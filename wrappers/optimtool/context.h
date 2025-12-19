#pragma once

#include <map>

struct EnableState
{
    EnableState()
    {

    }
    bool GL_BLEND; 
    bool GL_CULL_FACE; 

    bool GL_DEPTH_TEST;
    bool GL_SCISSOR_TEST; 
    bool GL_STENCIL_TEST;  

    bool GL_CLIP_DISTANCE ; 
    bool GL_COLOR_LOGIC_OP; 
    bool GL_DEBUG_OUTPUT; 
    bool GL_DEBUG_OUTPUT_SYNCHRONOUS; 
    bool GL_DEPTH_CLAMP; 
    
    bool GL_DITHER; 
    bool GL_FRAMEBUFFER_SRGB; 
    bool GL_LINE_SMOOTH; 
    bool GL_MULTISAMPLE ; 
    bool GL_POLYGON_OFFSET_FILL; 
    bool GL_POLYGON_OFFSET_LINE; 
    bool GL_POLYGON_OFFSET_POINT; 
    bool GL_POLYGON_SMOOTH; 

    bool GL_PRIMITIVE_RESTART; 
    bool GL_PRIMITIVE_RESTART_FIXED_INDEX; 
    bool GL_RASTERIZER_DISCARD; 
    bool GL_SAMPLE_ALPHA_TO_COVERAGE ; 
    bool GL_SAMPLE_ALPHA_TO_ONE; 
    bool GL_SAMPLE_COVERAGE; 
    bool GL_SAMPLE_SHADING; 
    bool GL_SAMPLE_MASK;

    bool GL_TEXTURE_CUBE_MAP_SEAMLESS; 
    bool GL_PROGRAM_POINT_SIZE ; 
};

struct BlendMode
{
    int m_srcMode;
    int m_dstMode;
    int m_srcAlphaMode;
    int m_dstAlphaMode;
};


#define GENERATE_GET_SET(variable_type, variable_name) \
private: \
    variable_type m_##variable_name; \
public: \
    inline variable_type get##variable_name() const { \
        return m_##variable_name; \
    } \
    inline unsigned set##variable_name(variable_type value) { \
        if(m_##variable_name == value) \
        { \
            return 1; \
        } \
        m_##variable_name = value; \
        return 0; \
    }

class Context
{
public:
    Context();
    Context(void* pHandle);
    ~Context();

    GENERATE_GET_SET(unsigned, ProgramUse)
    GENERATE_GET_SET(unsigned, VertexArrayBind)
    GENERATE_GET_SET(unsigned, FrameBufferBind)

private:
    EnableState m_EnableState;
    BlendMode m_BlendMode;
    std::map<unsigned, unsigned> m_ShaderSlotBufferMap;
    void* m_Handle;
};