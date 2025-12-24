#pragma once

#include "predef.h"

class State;
class DrawCall
{
public:
    DrawCall();

    ~DrawCall();

    void SetState(State* state)
    {
        m_pState = state;
    }

    State* GetState() const
    {
        return m_pState ;
    }

    void SetDrawParam(GLenum drawmode, GLenum elementType, unsigned startvbo, unsigned startebo, unsigned drawcount, unsigned instancecount);

    
    bool operator==(const DrawCall& other) const;
    bool operator<(const DrawCall& other) const;


    GLenum GetDrawMode()
    {
        return m_DrawMode;
    }

    GLenum GetElementType()
    {
        return m_ElementType;
    }

    unsigned GetStartVbo()
    {
        return m_StartVbo;
    }

    unsigned GetStartEbo()
    {
        return m_StartEbo;
    }

    unsigned GetDrawCount()
    {
        return m_DrawCount;
    }

    unsigned GetInstanceCount()
    {
        return m_InstanceCount;
    }
private:
    State* m_pState;

    GLenum m_DrawMode;
    GLenum m_ElementType;
    unsigned m_StartVbo;
    unsigned m_StartEbo;
    unsigned m_DrawCount;
    unsigned m_InstanceCount;

};