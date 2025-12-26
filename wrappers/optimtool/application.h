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

    void SetCollectMode(bool collect)
    {
        m_ColloectMode = collect;
    }

    bool GetCollectMode()
    {
        return m_ColloectMode;
    }

    bool GetDisableReadPixels()
    {
        return m_DisableReadPixels;
    }
private:
    Application();
    void* m_pCurrentContextHandle;
    std::map<void*,Context*> m_HandleContextMap;
    std::map<unsigned, ShaderParam> m_ShaderParamMapCache;
    bool m_ColloectMode;// 在收集状态下，会存储所有绘制相关的API调用，等到swapbuffer，bindframebuffer，flush，finish的时候再一次性调用。
    bool m_DisableReadPixels;//强行关闭glreadpixels函数。
};