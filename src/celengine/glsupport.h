#pragma once

#define NO_GLU

#ifdef USE_EPOXY
#ifdef _WIN32
#include <windows.h>
#endif
#include <epoxy/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#else
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef USE_MGL_NAMESPACE

// Manually define GLES2/3 functions

extern "C" {
extern void glGenFramebuffers(GLsizei n, GLuint* framebuffers);
extern void glBindFramebuffer(GLenum target, GLuint framebuffer);
extern void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern GLenum glCheckFramebufferStatus (GLenum target);
extern void glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers);
extern void glBindBuffer(GLenum target, GLuint buffer);
extern void glGenBuffers(GLsizei n, GLuint* buffers);
extern void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
extern void glUseProgram(GLuint program);
extern void *glMapBuffer(GLenum target, GLenum access);
extern GLboolean glUnmapBuffer(GLenum target);
extern void glShaderSource (GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length);
extern void glCompileShader(GLuint shader);
extern void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
extern void glDeleteShader(GLuint shader);
extern int glGetUniformLocation(GLuint program, const GLchar* name);
extern void glUniform1f (GLint location, GLfloat x);
extern void glUniform1fv (GLint location, GLsizei count, const GLfloat* v);
extern void glUniform1i (GLint location, GLint x);
extern void glUniform1iv (GLint location, GLsizei count, const GLint* v);
extern void glUniform2f (GLint location, GLfloat x, GLfloat y);
extern void glUniform2fv (GLint location, GLsizei count, const GLfloat* v);
extern void glUniform2i (GLint location, GLint x, GLint y);
extern void glUniform2iv (GLint location, GLsizei count, const GLint* v);
extern void glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z);
extern void glUniform3fv (GLint location, GLsizei count, const GLfloat* v);
extern void glUniform3i (GLint location, GLint x, GLint y, GLint z);
extern void glUniform3iv (GLint location, GLsizei count, const GLint* v);
extern void glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void glUniform4fv (GLint location, GLsizei count, const GLfloat* v);
extern void glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w);
extern void glUniform4iv (GLint location, GLsizei count, const GLint* v);
extern void glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern void glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
extern void glDeleteProgram (GLuint program);
extern void glAttachShader (GLuint program, GLuint shader);
extern void glLinkProgram (GLuint program);
extern void glGetProgramiv (GLuint program, GLenum pname, GLint* params);
extern GLuint glCreateShader(    GLenum shaderType);
extern GLuint glCreateProgram(    void);
extern GLboolean glIsShader (GLuint shader);
extern GLboolean glIsProgram (GLuint program);
extern void glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
extern void glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
extern void glEnableVertexAttribArray (GLuint index);
extern void glDisableVertexAttribArray (GLuint index);
extern void glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
extern void glDeleteBuffers (GLsizei n, const GLuint* buffers);
extern void glDeleteVertexArrays (GLsizei n, const GLuint* arrays);
extern void glGenVertexArrays (GLsizei n, GLuint* arrays);
extern void glBindVertexArray (GLuint array);
extern void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
extern void glBindAttribLocation (GLuint program, GLuint index, const GLchar* name);
extern int  glGetAttribLocation (GLuint program, const GLchar* name);
extern void glGenerateMipmap(GLenum target);
extern void glVertexAttrib4fv(GLuint index, const GLfloat *v);
extern void glVertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
extern void glVertexAttrib3fv(GLuint index, const GLfloat *v);
extern void glVertexAttrib1f(GLuint index, GLfloat v0);
}

#endif

#endif

namespace celestia
{
namespace gl
{

constexpr const int GL_2_1 = 21;

extern bool ARB_shader_texture_lod;
extern bool ARB_vertex_array_object;
extern bool EXT_framebuffer_object;
extern bool EXT_texture_compression_s3tc;
extern bool EXT_texture_filter_anisotropic;

bool init() noexcept;
bool checkVersion(int) noexcept;
} // gl
} // celestia
