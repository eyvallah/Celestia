#pragma once

#include <string>
#include <celutil/array_view.h>

#ifdef GL_ES
//#include <epoxy/gl.h>
#define GL_TEXTURE_BASE_LEVEL                                                      0x813C
#define GL_TEXTURE_BASE_LEVEL_SGIS                                                 0x813C
#define GL_TEXTURE_MAX_LEVEL                                                       0x813D
#define GL_TEXTURE_MAX_LEVEL_APPLE                                                 0x813D
#define GL_TEXTURE_MAX_LEVEL_SGIS                                                  0x813D
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                                           0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE                                         0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                                           0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE                                         0x83F3
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                                           0x83F3
#define GL_CLAMP_TO_BORDER_OES                                                     0x812D
#define GL_TEXTURE_BORDER_COLOR_OES                                                0x1004
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
/*
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GLES2/gl2ext.h>
*/
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <epoxy/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#endif

#ifdef GL_ES
#ifdef glDepthRange
#undef glDepthRange
#endif
#define glDepthRange glDepthRangef
#define glGenVertexArrays glGenVertexArraysOES
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#endif

namespace celestia
{
namespace gl
{

constexpr const int GL_2_1 = 21;

extern bool ARB_shader_texture_lod;
extern bool EXT_texture_compression_s3tc;
extern bool EXT_texture_filter_anisotropic;
#ifdef GL_ES
extern bool OES_vertex_array_object;
#else
extern bool ARB_vertex_array_object;
extern bool EXT_framebuffer_object;
#endif
extern GLint maxPointSize;
extern GLfloat maxLineWidth;

bool init(util::array_view<std::string> = {}) noexcept;
bool checkVersion(int) noexcept;
} // gl
} // celestia
