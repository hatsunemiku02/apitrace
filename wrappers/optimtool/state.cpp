#include <assert.h>

#include "state.h"
#include "application.h"


std::set<State> State::AllStates;

State::State()
    :m_BlendMode()
    , m_EnableState()
    INIT_VAR(UseProgram, 0)
    INIT_VAR(BindVertexArray, 0)
    INIT_VAR(BindFrameBuffer, 0)
{
}


State::~State()
{

}

void State::SetEnableState(const EnableState& state)
{
    m_EnableState = state;
}

void State::SetBlendState(const BlendMode& blendmode)
{
    m_BlendMode = blendmode;
}

void State::SetShaderParam()
{
    assert(m_UseProgram != 0);
    std::map<unsigned, ShaderParam>& shaderParamCache = Application::GetInstance().GetShaderParamMapCache();
    if (shaderParamCache.find(m_UseProgram) == shaderParamCache.end())
    {
        shaderParamCache.insert(std::make_pair(m_UseProgram, ShaderParam()));
    }
    assert(shaderParamCache.find(m_UseProgram) != shaderParamCache.end());
    m_ShaderParam = shaderParamCache[m_UseProgram];
}

bool State::operator==(const State& other) const
{
    return (m_UseProgram == other.m_UseProgram) && (m_BindVertexArray == other.m_BindVertexArray) && (m_BindFrameBuffer == other.m_BindFrameBuffer)
        && (m_EnableState == other.m_EnableState) && (m_BlendMode == other.m_BlendMode) && (m_ShaderParam == other.m_ShaderParam);
}

bool State::operator<(const State& other) const
{
    if (m_UseProgram != other.m_UseProgram) return m_UseProgram < other.m_UseProgram;
    if (m_BindVertexArray != other.m_BindVertexArray) return m_BindVertexArray < other.m_BindVertexArray;
    if (m_BindFrameBuffer != other.m_BindFrameBuffer) return m_BindFrameBuffer < other.m_BindFrameBuffer;
    
    if (m_EnableState != other.m_EnableState) return m_EnableState < other.m_EnableState;
    if (m_BlendMode != other.m_BlendMode) return m_BlendMode < other.m_BlendMode;
    if (m_ShaderParam != other.m_ShaderParam) return m_ShaderParam < other.m_ShaderParam;
    
    return false;
}

