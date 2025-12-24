#include "pipeline.h"
#include "state.h"
#include "shaderparam.h"
#include "glfooheader.h"
#include <algorithm>
#include <assert.h>

PipeLine::PipeLine()
    :m_pStateCache(new State())
{

}

PipeLine::~PipeLine()
{
    delete m_pStateCache;
    m_pStateCache = nullptr;
}

void PipeLine::AddDrawCall(const DrawCall& drawcall)
{
    m_DrawCallVec.emplace_back(drawcall);
    if (m_UsedStateSet.find(drawcall.GetState())==m_UsedStateSet.end())
    {
        m_UsedStateSet.insert(drawcall.GetState());
    }

    if (m_UsedShaderSet.find(drawcall.GetState()->getUseProgram()) == m_UsedShaderSet.end())
    {
        m_UsedShaderSet.insert(drawcall.GetState()->getUseProgram());
    }
}

void PipeLine::SortDrawCalls()
{
    std::sort(m_DrawCallVec.begin(), m_DrawCallVec.end());
}

void PipeLine::ApplyDrawCalls()
{
    for (int i=0;i< m_DrawCallVec.size();i++)
    {
        ApplyState(m_DrawCallVec[i].GetState());

        glDrawElements(m_DrawCallVec[i].GetDrawMode(), m_DrawCallVec[i].GetDrawCount(), m_DrawCallVec[i].GetElementType(), (void*)m_DrawCallVec[i].GetStartEbo());
    }
}

void PipeLine::ApplyState(const State* pState)
{
    if (pState->GetEnableState()!=m_pStateCache->GetEnableState())
    {
        ApplyEnableState(m_pStateCache->GetEnableState());
        m_pStateCache->SetEnableState(pState->GetEnableState());
    }
    if (pState->getUseProgram() != m_pStateCache->getUseProgram())
    {
        glUseProgram(pState->getUseProgram());
        m_pStateCache->setUseProgram(pState->getUseProgram());
    }

    if (pState->GetShaderParam() != m_pStateCache->GetShaderParam())
    {
        ApplyShaderParam(pState->GetShaderParam());
        m_pStateCache->SetShaderParam(pState->GetShaderParam());
    }

    if (pState->getBindVertexArray() != m_pStateCache->getBindVertexArray())
    {
        glBindVertexArray(pState->getBindVertexArray());
        m_pStateCache->setBindVertexArray(pState->getBindVertexArray());
    }
}


void PipeLine::ApplyShaderParam(const ShaderParam& param)
{
    const std::map<unsigned, std::shared_ptr<Param>>& cacheParam = m_pStateCache->GetShaderParam().GetSlotParamMap();

    const std::map<unsigned, std::shared_ptr<Param>>& setParam = param.GetSlotParamMap();

    for (auto itr = setParam.begin(); itr != setParam.end(); itr++)
    {
        auto cache_itr = cacheParam.find(itr->first);
        if (cache_itr == cacheParam.end() || !isEqual(itr->second, cache_itr->second))
        {
            ApplyOneShaderParam(itr->first, itr->second);
        }
    }
}


void PipeLine::ApplyOneShaderParam(unsigned slot, const std::shared_ptr<Param>& param)
{
    if (param->GetParamType() == ParamType::FLOAT4)
    {
        std::shared_ptr <ParamFloat4> pl = std::static_pointer_cast<ParamFloat4>(param);

    }
    else if (param->GetParamType() == ParamType::FLOATVEC)
    {
        std::shared_ptr <ParamFloatVec> pl = std::static_pointer_cast<ParamFloatVec>(param);
    }
    else if (param->GetParamType() == ParamType::TEXTURE)
    {
        std::shared_ptr <ParamTexture> pl = std::static_pointer_cast<ParamTexture>(param);
      
    }
    else if (param->GetParamType() == ParamType::BUFFER)
    {
        std::shared_ptr <ParamBuffer> pl = std::static_pointer_cast<ParamBuffer>(param);
        glBindBufferBase(GL_UNIFORM_BUFFER,slot, pl->GetBufferID());
    }
    else
    {
        printf("uknown param type\n");
        assert(false);
    }
}

void PipeLine::ApplyEnableState(const EnableState& pState)
{
    const EnableState& cache = m_pStateCache->GetEnableState();
    ApplyOneEnableState(GL_BLEND, cache.BLEND, pState.BLEND);
    ApplyOneEnableState(GL_CULL_FACE, cache.CULL_FACE, pState.CULL_FACE);
    ApplyOneEnableState(GL_DEPTH_TEST, cache.DEPTH_TEST, pState.DEPTH_TEST);
    ApplyOneEnableState(GL_SCISSOR_TEST, cache.SCISSOR_TEST, pState.SCISSOR_TEST);
    ApplyOneEnableState(GL_STENCIL_TEST, cache.STENCIL_TEST, pState.STENCIL_TEST);
    ApplyOneEnableState(GL_CLIP_DISTANCE1, cache.CLIP_DISTANCE1, pState.CLIP_DISTANCE1);
    ApplyOneEnableState(GL_COLOR_LOGIC_OP, cache.COLOR_LOGIC_OP, pState.COLOR_LOGIC_OP);
    ApplyOneEnableState(GL_DEBUG_OUTPUT, cache.DEBUG_OUTPUT, pState.DEBUG_OUTPUT);
    ApplyOneEnableState(GL_DEBUG_OUTPUT_SYNCHRONOUS, cache.DEBUG_OUTPUT_SYNCHRONOUS, pState.DEBUG_OUTPUT_SYNCHRONOUS);
    ApplyOneEnableState(GL_DEPTH_CLAMP, cache.DEPTH_CLAMP, pState.DEPTH_CLAMP);
    ApplyOneEnableState(GL_DITHER, cache.DITHER, pState.DITHER);
    ApplyOneEnableState(GL_FRAMEBUFFER_SRGB, cache.FRAMEBUFFER_SRGB, pState.FRAMEBUFFER_SRGB);
    ApplyOneEnableState(GL_LINE_SMOOTH, cache.LINE_SMOOTH, pState.LINE_SMOOTH);
    ApplyOneEnableState(GL_MULTISAMPLE, cache.MULTISAMPLE, pState.MULTISAMPLE);
    ApplyOneEnableState(GL_POLYGON_OFFSET_FILL, cache.POLYGON_OFFSET_FILL, pState.POLYGON_OFFSET_FILL);
    ApplyOneEnableState(GL_POLYGON_OFFSET_LINE, cache.POLYGON_OFFSET_LINE, pState.POLYGON_OFFSET_LINE);
    ApplyOneEnableState(GL_POLYGON_OFFSET_POINT, cache.POLYGON_OFFSET_POINT, pState.POLYGON_OFFSET_POINT);
    ApplyOneEnableState(GL_POLYGON_SMOOTH, cache.POLYGON_SMOOTH, pState.POLYGON_SMOOTH);
    ApplyOneEnableState(GL_PRIMITIVE_RESTART, cache.PRIMITIVE_RESTART, pState.PRIMITIVE_RESTART);
    ApplyOneEnableState(GL_PRIMITIVE_RESTART_FIXED_INDEX, cache.PRIMITIVE_RESTART_FIXED_INDEX, pState.PRIMITIVE_RESTART_FIXED_INDEX);
    ApplyOneEnableState(GL_RASTERIZER_DISCARD, cache.RASTERIZER_DISCARD, pState.RASTERIZER_DISCARD);
    ApplyOneEnableState(GL_SAMPLE_ALPHA_TO_COVERAGE, cache.SAMPLE_ALPHA_TO_COVERAGE, pState.SAMPLE_ALPHA_TO_COVERAGE);
    ApplyOneEnableState(GL_SAMPLE_ALPHA_TO_ONE, cache.SAMPLE_ALPHA_TO_ONE, pState.SAMPLE_ALPHA_TO_ONE);
    ApplyOneEnableState(GL_SAMPLE_COVERAGE, cache.SAMPLE_COVERAGE, pState.SAMPLE_COVERAGE);
    ApplyOneEnableState(GL_SAMPLE_SHADING, cache.SAMPLE_SHADING, pState.SAMPLE_SHADING);
    ApplyOneEnableState(GL_SAMPLE_MASK, cache.SAMPLE_MASK, pState.SAMPLE_MASK);
    ApplyOneEnableState(GL_TEXTURE_CUBE_MAP_SEAMLESS, cache.TEXTURE_CUBE_MAP_SEAMLESS, pState.TEXTURE_CUBE_MAP_SEAMLESS);
    ApplyOneEnableState(GL_PROGRAM_POINT_SIZE, cache.PROGRAM_POINT_SIZE, pState.PROGRAM_POINT_SIZE);
}

void PipeLine::ApplyOneEnableState(GLenum statename, bool isEnableCurrent,bool isEnable)
{
    if (isEnableCurrent==isEnable)
    {
        return;
    }
    if (isEnable)
    {
        glEnable(statename);
    }
    else
    {
        glDisable(statename);
    }
}

