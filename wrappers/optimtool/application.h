#pragma once
#include <map>
#include <set>
#include "shaderparam.h"

class Context;


class Application
{
public:
    ~Application();
    static Application& GetInstance();

    Context* CreateContext(void* handle);

    void SetCurrentContext(void* handle);
    Context* GetConotext(void* handle);
    Context* GetCurrentContext();

    void* GetCurrentContextHandle()
    {
        return m_pCurrentContextHandle;
    }

    std::map<unsigned, ShaderParam>& GetShaderParamMapCache()
    {
        return m_ShaderParamMapCache;
    }
private:
    Application();
    void* m_pCurrentContextHandle;
    std::map<void*,Context*> m_HandleContextMap;
    std::map<unsigned, ShaderParam> m_ShaderParamMapCache;
};