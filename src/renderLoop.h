#ifndef RENDERLOOP_H
#define RENDERLOOP_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat4x4.hpp>

void RenderLoop(GLFWwindow *&window, GLuint shaderProgramID, size_t vertexCount);

#endif
