#pragma once
#include <vector>
#include <set>
#include <memory>
#include "drawcall.h"
#include "predef.h"

class State;
class ShaderParam;
class Param;

class PipeLine
{
public:
    PipeLine();
    ~PipeLine();

    void AddDrawCall(const DrawCall& drawcall);

    void SortDrawCalls();

    void ApplyDrawCalls();


    std::vector<DrawCall>& GetDrawCallVec()
    {
        return m_DrawCallVec;
    }

    std::set<State*>& GetUsedStateSet()
    {
        return m_UsedStateSet;
    }
private:

    void ApplyState(const State* pState);

    void ApplyEnableState(const EnableState& pState);

    void ApplyOneEnableState(GLenum statename, bool isEnableCurrent,bool isEnable);

    void ApplyShaderParam(const ShaderParam& param);

    void ApplyOneShaderParam(unsigned slot,const std::shared_ptr<Param>& param);

    //void ApplyOneEnableState(bool isEnable);

    std::vector<DrawCall> m_DrawCallVec;
    std::set<State*> m_UsedStateSet;
    std::set<unsigned> m_UsedShaderSet;


    State* m_pStateCache;

};