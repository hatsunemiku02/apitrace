#include "application.h"
#include "context.h"

Application::Application()
:m_pCurrentContextHandle(nullptr)
{

}

Application::~Application()
{
    for (auto itr = m_HandleContextMap.begin();itr!=m_HandleContextMap.end();itr++)
    {
        delete itr->second;
        itr->second = nullptr;
    }
    m_HandleContextMap.clear();
}

Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

Context* Application::CreateContext(void* handle)
{
    printf("Application::CreateContext\n");
    Context* pCtx = new Context(handle);
    m_HandleContextMap.insert(std::make_pair(handle, pCtx));
    return pCtx;
}

void Application::SetCurrentContext(void* handle)
{
    printf("Application::SetCurrentContext\n");
    m_pCurrentContextHandle = handle;
}

Context* Application::GetConotext(void* handle)
{
    //printf("Application::GetConotext\n");
    if (m_HandleContextMap.find(handle)==m_HandleContextMap.end())
    {
        printf("Application::GetConotext failed. context not found.\n");
    }
    return m_HandleContextMap[handle];
}

Context* Application::GetCurrentContext()
{
    return GetConotext(m_pCurrentContextHandle);
}
