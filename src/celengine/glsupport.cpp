#include "glsupport.h"
#include <algorithm>
#include <cstring>

namespace celestia
{
namespace gl
{

#ifdef GL_ES
bool OES_vertex_array_object        = false;
bool OES_texture_border_clamp       = false;
#else
bool ARB_vertex_array_object        = false;
bool EXT_framebuffer_object         = false;
#endif
bool ARB_shader_texture_lod         = false;
bool EXT_texture_compression_s3tc   = false;
bool EXT_texture_filter_anisotropic = false;
bool MESA_pack_invert               = false;
GLint maxPointSize                  = 0;
GLfloat maxLineWidth                = 0.0f;

namespace
{
    inline bool has_extension(const char* name) noexcept
    {
//        return epoxy_has_gl_extension(name);
        const char *extensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
        return strstr(extensions, name) != nullptr;
    }

    bool check_extension(util::array_view<std::string> list, const char* name) noexcept
    {
        return std::find(list.begin(), list.end(), std::string(name)) == list.end() && has_extension(name);
    }
}

bool init(util::array_view<std::string> ignore) noexcept
{
#ifdef GL_ES
    OES_vertex_array_object        = check_extension(ignore, "GL_OES_vertex_array_object");
    OES_texture_border_clamp       = check_extension(ignore, "GL_OES_texture_border_clamp") || check_extension(ignore, "GL_EXT_texture_border_clamp") ;
#else
    ARB_vertex_array_object        = check_extension(ignore, "GL_ARB_vertex_array_object");
    EXT_framebuffer_object         = check_extension(ignore, "GL_EXT_framebuffer_object");
#endif
    ARB_shader_texture_lod         = check_extension(ignore, "GL_ARB_shader_texture_lod");
    EXT_texture_compression_s3tc   = check_extension(ignore, "GL_EXT_texture_compression_s3tc");
    EXT_texture_filter_anisotropic = check_extension(ignore, "GL_EXT_texture_filter_anisotropic");
    MESA_pack_invert               = check_extension(ignore, "GL_MESA_pack_invert");

    GLint pointSizeRange[2];
    GLfloat lineWidthRange[2];
#ifdef GL_ES
    glGetIntegerv(GL_ALIASED_POINT_SIZE_RANGE, pointSizeRange);
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
#else
    glGetIntegerv(GL_SMOOTH_POINT_SIZE_RANGE, pointSizeRange);
    glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, lineWidthRange);
#endif
    maxPointSize = pointSizeRange[1];
    maxLineWidth = lineWidthRange[1];

    return true;
}

bool checkVersion(int v) noexcept
{
    return true;
//    return epoxy_gl_version() >= v;
}
} // gl
} // celestia
