#include "predef.h"
#include "state.h"

// EnableState operator< implementation
bool EnableState::operator<(const EnableState& other) const
{
    // Compare each enable state in the order they are declared
    if (BLEND != other.BLEND) return BLEND < other.BLEND;
    if (CULL_FACE != other.CULL_FACE) return CULL_FACE < other.CULL_FACE;
    if (DEPTH_TEST != other.DEPTH_TEST) return DEPTH_TEST < other.DEPTH_TEST;
    if (SCISSOR_TEST != other.SCISSOR_TEST) return SCISSOR_TEST < other.SCISSOR_TEST;
    if (STENCIL_TEST != other.STENCIL_TEST) return STENCIL_TEST < other.STENCIL_TEST;
    if (CLIP_DISTANCE1 != other.CLIP_DISTANCE1) return CLIP_DISTANCE1 < other.CLIP_DISTANCE1;
    if (COLOR_LOGIC_OP != other.COLOR_LOGIC_OP) return COLOR_LOGIC_OP < other.COLOR_LOGIC_OP;
    if (DEBUG_OUTPUT != other.DEBUG_OUTPUT) return DEBUG_OUTPUT < other.DEBUG_OUTPUT;
    if (DEBUG_OUTPUT_SYNCHRONOUS != other.DEBUG_OUTPUT_SYNCHRONOUS) return DEBUG_OUTPUT_SYNCHRONOUS < other.DEBUG_OUTPUT_SYNCHRONOUS;
    if (DEPTH_CLAMP != other.DEPTH_CLAMP) return DEPTH_CLAMP < other.DEPTH_CLAMP;
    if (DITHER != other.DITHER) return DITHER < other.DITHER;
    if (FRAMEBUFFER_SRGB != other.FRAMEBUFFER_SRGB) return FRAMEBUFFER_SRGB < other.FRAMEBUFFER_SRGB;
    if (LINE_SMOOTH != other.LINE_SMOOTH) return LINE_SMOOTH < other.LINE_SMOOTH;
    if (MULTISAMPLE != other.MULTISAMPLE) return MULTISAMPLE < other.MULTISAMPLE;
    if (POLYGON_OFFSET_FILL != other.POLYGON_OFFSET_FILL) return POLYGON_OFFSET_FILL < other.POLYGON_OFFSET_FILL;
    if (POLYGON_OFFSET_LINE != other.POLYGON_OFFSET_LINE) return POLYGON_OFFSET_LINE < other.POLYGON_OFFSET_LINE;
    if (POLYGON_OFFSET_POINT != other.POLYGON_OFFSET_POINT) return POLYGON_OFFSET_POINT < other.POLYGON_OFFSET_POINT;
    if (POLYGON_SMOOTH != other.POLYGON_SMOOTH) return POLYGON_SMOOTH < other.POLYGON_SMOOTH;
    if (PRIMITIVE_RESTART != other.PRIMITIVE_RESTART) return PRIMITIVE_RESTART < other.PRIMITIVE_RESTART;
    if (PRIMITIVE_RESTART_FIXED_INDEX != other.PRIMITIVE_RESTART_FIXED_INDEX) return PRIMITIVE_RESTART_FIXED_INDEX < other.PRIMITIVE_RESTART_FIXED_INDEX;
    if (RASTERIZER_DISCARD != other.RASTERIZER_DISCARD) return RASTERIZER_DISCARD < other.RASTERIZER_DISCARD;
    if (SAMPLE_ALPHA_TO_COVERAGE != other.SAMPLE_ALPHA_TO_COVERAGE) return SAMPLE_ALPHA_TO_COVERAGE < other.SAMPLE_ALPHA_TO_COVERAGE;
    if (SAMPLE_ALPHA_TO_ONE != other.SAMPLE_ALPHA_TO_ONE) return SAMPLE_ALPHA_TO_ONE < other.SAMPLE_ALPHA_TO_ONE;
    if (SAMPLE_COVERAGE != other.SAMPLE_COVERAGE) return SAMPLE_COVERAGE < other.SAMPLE_COVERAGE;
    if (SAMPLE_SHADING != other.SAMPLE_SHADING) return SAMPLE_SHADING < other.SAMPLE_SHADING;
    if (SAMPLE_MASK != other.SAMPLE_MASK) return SAMPLE_MASK < other.SAMPLE_MASK;
    if (TEXTURE_CUBE_MAP_SEAMLESS != other.TEXTURE_CUBE_MAP_SEAMLESS) return TEXTURE_CUBE_MAP_SEAMLESS < other.TEXTURE_CUBE_MAP_SEAMLESS;
    if (PROGRAM_POINT_SIZE != other.PROGRAM_POINT_SIZE) return PROGRAM_POINT_SIZE < other.PROGRAM_POINT_SIZE;
    return false;
}

bool EnableState::operator==(const EnableState& other) const
{
    return BLEND == other.BLEND &&
        CULL_FACE == other.CULL_FACE &&
        DEPTH_TEST == other.DEPTH_TEST &&
        SCISSOR_TEST == other.SCISSOR_TEST &&
        STENCIL_TEST == other.STENCIL_TEST &&
        CLIP_DISTANCE1 == other.CLIP_DISTANCE1 &&
        COLOR_LOGIC_OP == other.COLOR_LOGIC_OP &&
        DEBUG_OUTPUT == other.DEBUG_OUTPUT &&
        DEBUG_OUTPUT_SYNCHRONOUS == other.DEBUG_OUTPUT_SYNCHRONOUS &&
        DEPTH_CLAMP == other.DEPTH_CLAMP &&
        DITHER == other.DITHER &&
        FRAMEBUFFER_SRGB == other.FRAMEBUFFER_SRGB &&
        LINE_SMOOTH == other.LINE_SMOOTH &&
        MULTISAMPLE == other.MULTISAMPLE &&
        POLYGON_OFFSET_FILL == other.POLYGON_OFFSET_FILL &&
        POLYGON_OFFSET_LINE == other.POLYGON_OFFSET_LINE &&
        POLYGON_OFFSET_POINT == other.POLYGON_OFFSET_POINT &&
        POLYGON_SMOOTH == other.POLYGON_SMOOTH &&
        PRIMITIVE_RESTART == other.PRIMITIVE_RESTART &&
        PRIMITIVE_RESTART_FIXED_INDEX == other.PRIMITIVE_RESTART_FIXED_INDEX &&
        RASTERIZER_DISCARD == other.RASTERIZER_DISCARD &&
        SAMPLE_ALPHA_TO_COVERAGE == other.SAMPLE_ALPHA_TO_COVERAGE &&
        SAMPLE_ALPHA_TO_ONE == other.SAMPLE_ALPHA_TO_ONE &&
        SAMPLE_COVERAGE == other.SAMPLE_COVERAGE &&
        SAMPLE_SHADING == other.SAMPLE_SHADING &&
        SAMPLE_MASK == other.SAMPLE_MASK &&
        TEXTURE_CUBE_MAP_SEAMLESS == other.TEXTURE_CUBE_MAP_SEAMLESS &&
        PROGRAM_POINT_SIZE == other.PROGRAM_POINT_SIZE;
}

bool EnableState::operator!=(const EnableState& other) const
{
    return !(*this == other);
}


bool BlendMode::operator<(const BlendMode& other) const
{
    if (m_srcMode != other.m_srcMode) return m_srcMode < other.m_srcMode;
    if (m_dstMode != other.m_dstMode) return m_dstMode < other.m_dstMode;
    if (m_srcAlphaMode != other.m_srcAlphaMode) return m_srcAlphaMode < other.m_srcAlphaMode;
    if (m_dstAlphaMode != other.m_dstAlphaMode) return m_dstAlphaMode < other.m_dstAlphaMode;
    return false;
}

bool BlendMode::operator==(const BlendMode& other) const
{
    return m_srcMode == other.m_srcMode &&
        m_dstMode == other.m_dstMode &&
        m_srcAlphaMode == other.m_srcAlphaMode &&
        m_dstAlphaMode == other.m_dstAlphaMode;
}

bool BlendMode::operator!=(const BlendMode& other) const
{
    return !(*this == other);
}


