#include "context.h"

Context::Context()
    :m_Handle(nullptr)
    INIT_VAR(ProgramUse)
    INIT_VAR(VertexArrayBind)
    INIT_VAR(FrameBufferBind)
{
}

Context::Context(void* pHandle)
{
    m_Handle = pHandle;
}

Context::~Context()
{

}
