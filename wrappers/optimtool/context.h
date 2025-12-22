#pragma once

#include <map>

struct EnableState
{
    EnableState()
    {

    }
    bool BLEND; 
    bool CULL_FACE; 

    bool DEPTH_TEST;
    bool SCISSOR_TEST; 
    bool STENCIL_TEST;  

    bool CLIP_DISTANCE ; 
    bool COLOR_LOGIC_OP; 
    bool DEBUG_OUTPUT; 
    bool DEBUG_OUTPUT_SYNCHRONOUS; 
    bool DEPTH_CLAMP; 
    
    bool DITHER; 
    bool FRAMEBUFFER_SRGB; 
    bool LINE_SMOOTH; 
    bool MULTISAMPLE ; 
    bool POLYGON_OFFSET_FILL; 
    bool POLYGON_OFFSET_LINE; 
    bool POLYGON_OFFSET_POINT; 
    bool POLYGON_SMOOTH; 

    bool PRIMITIVE_RESTART; 
    bool PRIMITIVE_RESTART_FIXED_INDEX; 
    bool RASTERIZER_DISCARD; 
    bool SAMPLE_ALPHA_TO_COVERAGE ; 
    bool SAMPLE_ALPHA_TO_ONE; 
    bool SAMPLE_COVERAGE; 
    bool SAMPLE_SHADING; 
    bool SAMPLE_MASK;

    bool TEXTURE_CUBE_MAP_SEAMLESS; 
    bool PROGRAM_POINT_SIZE ; 
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



#define INIT_VAR(variable_name,val) \
    ,m_##variable_name(val)

class Context
{
public:
    Context();
    Context(void* pHandle);
    ~Context();

    GENERATE_GET_SET(unsigned, UseProgram)
    GENERATE_GET_SET(unsigned, BindVertexArray)
    GENERATE_GET_SET(unsigned, BindFrameBuffer)

private:
    EnableState m_EnableState;
    BlendMode m_BlendMode;
    std::map<unsigned, unsigned> m_ShaderSlotBufferMap;
    void* m_Handle;
};