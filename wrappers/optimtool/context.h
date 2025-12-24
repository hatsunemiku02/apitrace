#pragma once

#include <vector>
#include <map>
#include <assert.h>
#include "predef.h"
#include "shaderparam.h"


class State;
class PipeLine;

class Context
{
public:
    Context();
    Context(void* pHandle);
    ~Context();

    void BeginFrame();
    void BeginPipeLine();
    void AddDrawCall(GLenum drawmode, GLenum elementType, unsigned startvbo, unsigned startebo, unsigned drawcount, unsigned instancecount);
    void EndPipeLine();
    void SetEnable(GLenum state);
    void SetDisable(GLenum state);

    int SetProgramUniform(unsigned pg, unsigned locate, void* value, unsigned datalength, ParamType overrideType = ParamType::UNKNOWN);
    int SetProgramUniform(unsigned locate, void* value, unsigned datalength, ParamType overrideType = ParamType::UNKNOWN);
    
    void SetActiveTexUnit(GLenum texUnit)
    {
        int m_ActiveTextureUnit = texUnit - GL_TEXTURE0;
        assert(m_ActiveTextureUnit >= 0);
    }

    void BindTexToTexUnit(GLenum texUnit, unsigned texID)
    {
        m_TexUnitIDMap[texUnit] = texID;
    }

    void BindTex( unsigned texID)
    {
        m_TexUnitIDMap[m_ActiveTextureUnit] = texID;
    }

public:

    GENERATE_GET_SET(unsigned, UseProgram)
    GENERATE_GET_SET(unsigned, BindVertexArray)
    GENERATE_GET_SET(unsigned, BindFrameBuffer)

private:
    void gernateState();
    
private:
    void* m_Handle;
    EnableState m_EnableState;
    BlendMode m_BlendMode;    

    int m_ActiveTextureUnit;
    std::map<int, unsigned> m_TexUnitIDMap;
    std::vector<PipeLine*> m_PipelinesThisFrame;
    unsigned int m_FrameCount;
};