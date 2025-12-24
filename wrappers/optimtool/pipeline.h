#pragma once
#include <vector>
#include <set>
#include "drawcall.h"


class State;
class PipeLine
{
public:
    PipeLine();
    ~PipeLine();

    void AddDrawCall(const DrawCall& drawcall);

    std::vector<DrawCall>& GetDrawCallVec()
    {
        return m_DrawCallVec;
    }

    std::set<State*>& GetUsedStateSet()
    {
        return m_UsedStateSet;
    }
private:

    std::vector<DrawCall> m_DrawCallVec;
    std::set<State*> m_UsedStateSet;
    std::set<unsigned> m_UsedShaderSet;
};