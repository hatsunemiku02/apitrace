#pragma once
#include <map>

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
private:
    Application();
    void* m_pCurrentContextHandle;
    std::map<void*,Context*> m_HandleContextMap;
};