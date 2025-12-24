#include "pipeline.h"
#include "state.h"
PipeLine::PipeLine()
{

}

PipeLine::~PipeLine()
{

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

