#pragma once



#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,NAME,...) NAME

#define FOR_EACH(action,...) \
    GET_MACRO(__VA_ARGS__,FOR_EACH_30,FOR_EACH_29,FOR_EACH_28,FOR_EACH_27,FOR_EACH_26,FOR_EACH_25,FOR_EACH_24,FOR_EACH_23,FOR_EACH_22,FOR_EACH_21,FOR_EACH_20,\
FOR_EACH_19,FOR_EACH_18,FOR_EACH_17,FOR_EACH_16,FOR_EACH_15,FOR_EACH_14,FOR_EACH_13,FOR_EACH_12,FOR_EACH_11,FOR_EACH_10,\
FOR_EACH_9,FOR_EACH_8,FOR_EACH_7,FOR_EACH_6,FOR_EACH_5, FOR_EACH_4, FOR_EACH_3, FOR_EACH_2, FOR_EACH_1)(action,__VA_ARGS__)\

#define FOR_EACH_1(action,var) action(var)
#define FOR_EACH_2(action,var,...) action(var) FOR_EACH_1(action,__VA_ARGS__)
#define FOR_EACH_3(action,var,...) action(var) FOR_EACH_2(action,__VA_ARGS__)
#define FOR_EACH_4(action,var,...) action(var) FOR_EACH_3(action,__VA_ARGS__)
#define FOR_EACH_5(action,var,...) action(var) FOR_EACH_4(action,__VA_ARGS__)
#define FOR_EACH_6(action,var,...) action(var) FOR_EACH_5(action,__VA_ARGS__)
#define FOR_EACH_7(action,var,...) action(var) FOR_EACH_6(action,__VA_ARGS__)
#define FOR_EACH_8(action,var,...) action(var) FOR_EACH_7(action,__VA_ARGS__)
#define FOR_EACH_9(action,var,...) action(var) FOR_EACH_8(action,__VA_ARGS__)
#define FOR_EACH_10(action,var,...) action(var) FOR_EACH_9(action,__VA_ARGS__)
#define FOR_EACH_11(action,var,...) action(var) FOR_EACH_10(action,__VA_ARGS__)
#define FOR_EACH_12(action,var,...) action(var) FOR_EACH_11(action,__VA_ARGS__)
#define FOR_EACH_13(action,var,...) action(var) FOR_EACH_12(action,__VA_ARGS__)
#define FOR_EACH_14(action,var,...) action(var) FOR_EACH_13(action,__VA_ARGS__)
#define FOR_EACH_15(action,var,...) action(var) FOR_EACH_14(action,__VA_ARGS__)
#define FOR_EACH_16(action,var,...) action(var) FOR_EACH_15(action,__VA_ARGS__)
#define FOR_EACH_17(action,var,...) action(var) FOR_EACH_16(action,__VA_ARGS__)
#define FOR_EACH_18(action,var,...) action(var) FOR_EACH_17(action,__VA_ARGS__)
#define FOR_EACH_19(action,var,...) action(var) FOR_EACH_18(action,__VA_ARGS__)
#define FOR_EACH_20(action,var,...) action(var) FOR_EACH_19(action,__VA_ARGS__)
#define FOR_EACH_21(action,var,...) action(var) FOR_EACH_20(action,__VA_ARGS__)
#define FOR_EACH_22(action,var,...) action(var) FOR_EACH_21(action,__VA_ARGS__)
#define FOR_EACH_23(action,var,...) action(var) FOR_EACH_22(action,__VA_ARGS__)
#define FOR_EACH_24(action,var,...) action(var) FOR_EACH_23(action,__VA_ARGS__)
#define FOR_EACH_25(action,var,...) action(var) FOR_EACH_24(action,__VA_ARGS__)
#define FOR_EACH_26(action,var,...) action(var) FOR_EACH_25(action,__VA_ARGS__)
#define FOR_EACH_27(action,var,...) action(var) FOR_EACH_26(action,__VA_ARGS__)
#define FOR_EACH_28(action,var,...) action(var) FOR_EACH_27(action,__VA_ARGS__)
#define FOR_EACH_29(action,var,...) action(var) FOR_EACH_28(action,__VA_ARGS__)
#define FOR_EACH_30(action,var,...) action(var) FOR_EACH_29(action,__VA_ARGS__)



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

#define  STATE_SET( state,val )\
case GL_##state:\
    state = val; \
    break;\

#define  STATE_TRUE( state )\
    STATE_SET(state,true)


#define  STATE_FALSE( state )\
    STATE_SET(state,false)

#define DOT_SEP ,\

#define ENABLE_STATE_ACT_VAR(pre,act,aft) \
pre  act(BLEND                          ) aft  \
pre  act(CULL_FACE                      ) aft  \
pre  act(DEPTH_TEST                     ) aft  \
pre  act(SCISSOR_TEST                   ) aft  \
pre  act(STENCIL_TEST                   ) aft  \
pre  act(CLIP_DISTANCE1                 ) aft  \
pre  act(COLOR_LOGIC_OP                 ) aft  \
pre  act(DEBUG_OUTPUT                   ) aft  \
pre  act(DEBUG_OUTPUT_SYNCHRONOUS       ) aft  \
pre  act(DEPTH_CLAMP                    ) aft  \
pre  act(DITHER                         ) aft  \
pre  act(FRAMEBUFFER_SRGB               ) aft  \
pre  act(LINE_SMOOTH                    ) aft  \
pre  act(MULTISAMPLE                    ) aft  \
pre  act(POLYGON_OFFSET_FILL            ) aft  \
pre  act(POLYGON_OFFSET_LINE            ) aft  \
pre  act(POLYGON_OFFSET_POINT           ) aft  \
pre  act(POLYGON_SMOOTH                 ) aft  \
pre  act(PRIMITIVE_RESTART              ) aft  \
pre  act(PRIMITIVE_RESTART_FIXED_INDEX  ) aft  \
pre  act(RASTERIZER_DISCARD             ) aft  \
pre  act(SAMPLE_ALPHA_TO_COVERAGE       ) aft  \
pre  act(SAMPLE_ALPHA_TO_ONE            ) aft  \
pre  act(SAMPLE_COVERAGE                ) aft  \
pre  act(SAMPLE_SHADING                 ) aft  \
pre  act(SAMPLE_MASK                    ) aft  \
pre  act(TEXTURE_CUBE_MAP_SEAMLESS      ) aft  \
pre  act(PROGRAM_POINT_SIZE             ) aft  \

#define ENABLE_STATE_VAR(pre,aft) \
pre  BLEND                         aft  \
pre  CULL_FACE                     aft  \
pre  DEPTH_TEST                    aft  \
pre  SCISSOR_TEST                  aft  \
pre  STENCIL_TEST                  aft  \
pre  CLIP_DISTANCE1                aft  \
pre  COLOR_LOGIC_OP                aft  \
pre  DEBUG_OUTPUT                  aft  \
pre  DEBUG_OUTPUT_SYNCHRONOUS      aft  \
pre  DEPTH_CLAMP                   aft  \
pre  DITHER                        aft  \
pre  FRAMEBUFFER_SRGB              aft  \
pre  LINE_SMOOTH                   aft  \
pre  MULTISAMPLE                   aft  \
pre  POLYGON_OFFSET_FILL           aft  \
pre  POLYGON_OFFSET_LINE           aft  \
pre  POLYGON_OFFSET_POINT          aft  \
pre  POLYGON_SMOOTH                aft  \
pre  PRIMITIVE_RESTART             aft  \
pre  PRIMITIVE_RESTART_FIXED_INDEX aft  \
pre  RASTERIZER_DISCARD            aft  \
pre  SAMPLE_ALPHA_TO_COVERAGE      aft  \
pre  SAMPLE_ALPHA_TO_ONE           aft  \
pre  SAMPLE_COVERAGE               aft  \
pre  SAMPLE_SHADING                aft  \
pre  SAMPLE_MASK                   aft  \
pre  TEXTURE_CUBE_MAP_SEAMLESS     aft  \
pre  PROGRAM_POINT_SIZE            aft  \

#include "glproc.hpp"
#include <cstdio>


struct EnableState
{
    EnableState()
        :ENABLE_STATE_VAR(,(false)DOT_SEP)
        dummy(false)
    {

    }

    void Enable(GLenum state)
    {
        switch(state)
        {
            ENABLE_STATE_ACT_VAR(,STATE_TRUE, )
        default:
            printf("enable unknown state!\n");
            break;
        }
    }

    void Disable(GLenum state)
    {
        switch (state)
        {
            ENABLE_STATE_ACT_VAR(, STATE_FALSE, )
        default:
            printf("enable unknown state!\n");
            break;
        }
    }
    ENABLE_STATE_VAR(bool, ;)
    bool dummy;

    bool operator<(const EnableState& other) const;
    bool operator==(const EnableState& other) const;
    bool operator!=(const EnableState& other) const;
   
};

struct BlendMode
{
    BlendMode()
        :m_srcMode(0)
        , m_dstMode(0)
        , m_srcAlphaMode(0)
        , m_dstAlphaMode(0)
    {

    }

    void SetBlendMode(GLenum src, GLenum dst, GLenum srcAlp, GLenum dstAlp)
    {
        m_srcMode = src;
        m_dstMode = dst;
        m_srcAlphaMode = srcAlp;
        m_dstAlphaMode = dstAlp;
    }

    GLenum m_srcMode;
    GLenum m_dstMode;
    GLenum m_srcAlphaMode;
    GLenum m_dstAlphaMode;

    bool operator<(const BlendMode& other) const;
    bool operator==(const BlendMode& other) const;
    bool operator!=(const BlendMode& other) const;
};