#pragma once
#include "predef.h"
#include "shaderparam.h"
#include <set>



class State
{
public:
    State();
    ~State();

    GENERATE_GET_SET(unsigned, UseProgram)
    GENERATE_GET_SET(unsigned, BindVertexArray)
    GENERATE_GET_SET(unsigned, BindFrameBuffer)
       
public:
    static std::set<State> AllStates;

    void SetEnableState( const EnableState& state);
    void SetBlendState(const BlendMode& blendmode);
    void SetShaderParam(const ShaderParam& param);
    void SetShaderParam();

    const EnableState& GetEnableState() const
    {
        return m_EnableState;
    }

    const BlendMode& GetBlendMode() const
    {
        return m_BlendMode;
    }

    const ShaderParam& GetShaderParam() const
    {
        return m_ShaderParam;
    }

    bool operator==(const State& other) const;
    bool operator<(const State& other) const;
private:
    EnableState m_EnableState;
    BlendMode m_BlendMode;
    ShaderParam m_ShaderParam;
};