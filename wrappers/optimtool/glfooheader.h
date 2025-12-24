#pragma once
#include "os.hpp"
//#include <Windef.h>
extern "C" PUBLIC
void APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);

extern "C" PUBLIC
void APIENTRY glUseProgram(GLuint program);

extern "C" PUBLIC
void APIENTRY glBindVertexArray(GLuint array);

extern "C" PUBLIC
void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer);

extern "C" PUBLIC
void APIENTRY glDisable(GLenum cap);

extern "C" PUBLIC
void APIENTRY glEnable(GLenum cap);
