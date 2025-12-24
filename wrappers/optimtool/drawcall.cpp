#include "drawcall.h"
#include "state.h"



DrawCall::DrawCall()
:m_pState(nullptr)
, m_DrawMode(0)
, m_ElementType(0)
, m_StartVbo(0)
, m_StartEbo(0)
, m_DrawCount(0)
, m_InstanceCount(0)
{

}

DrawCall::~DrawCall()
{

}

void DrawCall::SetDrawParam(GLenum drawmode, GLenum elementType, unsigned startvbo, unsigned startebo, unsigned drawcount, unsigned instancecount)
{
    m_DrawMode = drawmode;
    m_ElementType = elementType;
    m_StartVbo = startvbo;
    m_StartEbo = startebo;
    m_DrawCount = drawcount;
    m_InstanceCount = instancecount;
}

bool DrawCall::operator<(const DrawCall& other) const
{
    if (m_pState != other.m_pState)
    {
        return m_pState < other.m_pState;
    }
    if (m_DrawMode != other.m_DrawMode)
    {
        return m_DrawMode < other.m_DrawMode;
    }
    if (m_ElementType != other.m_ElementType)
    {
        return m_ElementType < other.m_ElementType;
    }
    if (m_StartVbo != other.m_StartVbo)
    {
        return m_StartVbo < other.m_StartVbo;
    }
    if (m_StartEbo != other.m_StartEbo)
    {
        return m_StartEbo < other.m_StartEbo;
    }
    if (m_DrawCount != other.m_DrawCount)
    {
        return m_DrawCount < other.m_DrawCount;
    }
    if (m_InstanceCount != other.m_InstanceCount)
    {
        return m_InstanceCount < other.m_InstanceCount;
    }
    return false;
}

bool DrawCall::operator==(const DrawCall& other) const
{
    return m_pState == other.m_pState &&
        m_DrawMode == other.m_DrawMode &&
        m_ElementType == other.m_ElementType &&
        m_StartVbo == other.m_StartVbo &&
        m_StartEbo == other.m_StartEbo &&
        m_DrawCount == other.m_DrawCount &&
        m_InstanceCount == other.m_InstanceCount;
}

