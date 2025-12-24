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

