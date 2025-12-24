#include "context.h"
#include "State.h"
#include "application.h"
#include "pipeline.h"
#include "drawcall.h"
#include <stdexcept>
#include <iostream>

Context::Context()
    :m_Handle(nullptr)
    INIT_VAR(UseProgram,0)
    INIT_VAR(BindVertexArray,0)
    INIT_VAR(BindFrameBuffer,0)
    , m_ActiveTextureUnit(0)
    , m_TexUnitIDMap()
    , m_PipelinesThisFrame()
    , m_FrameCount(0)
{

}

Context::Context(void* pHandle)
    : m_Handle(pHandle)
    INIT_VAR(UseProgram, 0)
    INIT_VAR(BindVertexArray, 0)
    INIT_VAR(BindFrameBuffer, 0)
    , m_ActiveTextureUnit(0)
    , m_TexUnitIDMap()
    , m_PipelinesThisFrame()
    , m_FrameCount(0)
{

}

Context::~Context()
{

}

void Context::BeginFrame()
{
    for (int i=0;i< m_PipelinesThisFrame.size();i++)
    {
        delete m_PipelinesThisFrame[i];
        m_PipelinesThisFrame[i] = nullptr;
    }
    m_PipelinesThisFrame.clear();
}

void Context::BeginPipeLine()
{
    m_PipelinesThisFrame.push_back(new PipeLine());
}

void Context::AddDrawCall(GLenum drawmode, GLenum elementType, unsigned startvbo, unsigned startebo, unsigned drawcount, unsigned instancecount)
{
    printf("Context::AddDrawCall\n");
    State drawState;
    drawState.setUseProgram(m_UseProgram);
    drawState.setBindFrameBuffer(m_BindFrameBuffer);
    drawState.setBindVertexArray(m_BindVertexArray);
    drawState.SetShaderParam();

    if ( State::AllStates.find(drawState) == State::AllStates.end() )
    {
        printf("--Context::AddDrawCall:addnewstate\n");
        State::AllStates.insert(drawState);
    }


    printf("--Context::AddDrawCall:SetDrawParam\n");
    DrawCall drawCall;
    drawCall.SetDrawParam(drawmode,  elementType,  startvbo,  startebo,  drawcount,  instancecount);
    printf("--Context::AddDrawCall:State::AllStates.find \n");

    std::set<State>::iterator itr = State::AllStates.end();
    try {
        itr = State::AllStates.find(drawState);
    }
    catch (const std::exception& e) { // 捕获标准库异常及其派生类
        std::cerr << "捕获到标准异常: " << e.what() << std::endl;
    }
    catch (...) { // 捕获所有其他类型的异常（不推荐作为首选，但可作为兜底）
        std::cerr << "捕获到未知类型的异常" << std::endl;
    }
    
    assert(itr != State::AllStates.end());
    printf("--Context::AddDrawCall:State::AllStates.cast\n");
    State* pState = const_cast<State*>(&(*itr));
    printf("--Context::AddDrawCall:SetState\n");
    drawCall.SetState(pState);
    printf("--Context::AddDrawCall:AddDrawCall\n");
    m_PipelinesThisFrame[m_PipelinesThisFrame.size() - 1]->AddDrawCall(drawCall);
    printf("Context::AddDrawCall END\n");

}

static int startframe = 5;

void Context::EndPipeLine()
{
    printf("Context::EndPipeLine\n");
    //执行排序，相同state的drawcall放到一起
    printf("***********pipline info************************\n");
    if (m_PipelinesThisFrame.size()>=1)
    {
        printf("draw call count %d\n", m_PipelinesThisFrame[m_PipelinesThisFrame.size() - 1]->GetDrawCallVec().size());
        printf("used State Count %d\n", m_PipelinesThisFrame[m_PipelinesThisFrame.size() - 1]->GetUsedStateSet().size());
    }
    if (Application::GetInstance().GetCollectMode() == true)
    {
        Application::GetInstance().SetCollectMode(false);
        for (int i = 0; i < m_PipelinesThisFrame.size(); i++)
        {
            m_PipelinesThisFrame[i]->SortDrawCalls();
            m_PipelinesThisFrame[i]->ApplyDrawCalls();
        }
        Application::GetInstance().SetCollectMode(true);
    }
    printf("***********pipline info end************************\n");
    if (m_FrameCount==startframe)
    {
        Application::GetInstance().SetCollectMode(true);
    }
    if (m_FrameCount<= startframe)
    {
        m_FrameCount++;
    }
   
}

int Context::SetProgramUniform(unsigned pg, unsigned locate, void* value,unsigned datalength, ParamType overrideType)
{
    printf("Context::SetProgramUniform\n");
    std::map<unsigned, ShaderParam>& shaderParamCache = Application::GetInstance().GetShaderParamMapCache();
    if (shaderParamCache.find(pg)==shaderParamCache.end())
    {
        shaderParamCache.insert(std::make_pair(pg, ShaderParam(pg)));
    }

    ShaderParam& shaderParam = shaderParamCache[pg];

    if (overrideType!=ParamType::UNKNOWN)
    {
        if (overrideType==ParamType::BUFFER)
        {
            return shaderParam.SetParam(locate, std::make_shared<ParamBuffer>((*(unsigned*)value)) );
        }
        else if (overrideType == ParamType::TEXTURE)
        {
            unsigned texID = m_TexUnitIDMap[(*(int*)value)];
            return shaderParam.SetParam(locate, std::make_shared<ParamTexture>(texID));
        }
        else if (overrideType == ParamType::FLOATVEC)
        {
            return shaderParam.SetParam(locate, std::make_shared<ParamFloatVec>((float*)value,datalength));
        }

        return 1;
    }

    GLchar name[128];
    GLsizei length;
    GLint size;
    GLenum type; // 这个变量将保存uniform的类型枚举值


    printf(" Context::SetProgramUniform STEP1 \n");

    _glGetActiveUniform(pg, locate, sizeof(name), &length, &size, &type, name);
    printf("uniform type is %#X\n", type);
   
    if (type == GL_TEXTURE_3D
        || type == GL_TEXTURE_2D
        || type == GL_TEXTURE_1D
        || type == GL_TEXTURE_CUBE_MAP)
    {
        unsigned texID = m_TexUnitIDMap[(*(int*)value)];
        //m_ShaderSlotBufferMap[locate] = texID;
        return shaderParam.SetParam(locate, std::make_shared<ParamTexture>(texID));
    }
    else if (GL_FLOAT)
    {
        return shaderParam.SetParam(locate, std::make_shared<ParamFloatVec>((float*)value,1));
    }
    else if (GL_FLOAT_VEC2)
    {
        return shaderParam.SetParam(locate, std::make_shared<ParamFloatVec>((float*)value, 2));
    }
    else if (GL_FLOAT_VEC3)
    {
        return shaderParam.SetParam(locate, std::make_shared<ParamFloatVec>((float*)value, 3));
    }
    else if (GL_FLOAT_VEC4)
    {
        return shaderParam.SetParam(locate, std::make_shared<ParamFloatVec>((float*)value, 4));
    }
    else if (GL_UNIFORM_BUFFER)
    {
        return shaderParam.SetParam(locate, std::make_shared<ParamBuffer>((*(unsigned*)value)));
    }
    else
    {
        printf("Context::SetProgramUniform not implemented yet\n");
        printf("uniform type is %#X\n", type);
    }
    return 1;
}

int Context::SetProgramUniform(unsigned locate, void* value, unsigned datalength, ParamType overrideType)
{
    return SetProgramUniform(m_UseProgram,locate, value, datalength,overrideType);
}

void Context::SetEnable(GLenum state)
{
    m_EnableState.Enable(state);
}

void Context::SetDisable(GLenum state)
{
    m_EnableState.Disable(state);
}
