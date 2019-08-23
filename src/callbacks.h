#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <glfw/glfw3.h>

void keyboard(GLFWwindow *window, int key, int scancode, int action, int modifier);

void cursor(GLFWwindow *window, double x, double y);

void resize(GLFWwindow *window, int width, int height);

#endif
