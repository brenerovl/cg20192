#ifndef SHADERS_H
#define SHADERS_H
#include <string>
#include <glfw/glfw3.h>

bool compileShader(const std::string &filename, GLenum type, GLuint &id);
bool createProgram(const std::string &name, GLuint &id);

#endif

