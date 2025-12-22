#include "context.h"

Context::Context()
    :m_Handle(nullptr)
    INIT_VAR(UseProgram,0)
    INIT_VAR(BindVertexArray,0)
    INIT_VAR(BindFrameBuffer,0)
{
}

Context::Context(void* pHandle)
{
    m_Handle = pHandle;
}

Context::~Context()
{

}
