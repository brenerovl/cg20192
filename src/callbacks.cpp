#include "callbacks.h"

#include <glfw/glfw3.h>
#include <glm/ext.hpp>

#include "globals.h"
#include <iostream>

float FoV = 90.0f;
float AspectRatio = 1.0f;

void recalculateProjection()
{
    float f = 2 * glm::atan(glm::tan(glm::radians(FoV) / 2) / AspectRatio);
    // camera FoV, aspect ratio, clipping range, view distance
    PROJECTION = glm::perspective(f, AspectRatio, 0.001f, 1000.0f);

    std::cout << "FoV: " << FoV << " (" << f << ")";
    std::cout << ", Aspect ratio: " << AspectRatio << std::endl;
}

// Keyboard event callback
void keyboard(GLFWwindow *window, int key, int scancode, int action, int modifier)
{
    const float movementSpeed = 0.1f;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        KillWindow = true;

    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        MODEL = glm::translate(MODEL, glm::vec3(-1 * movementSpeed, 0 * movementSpeed, 0 * movementSpeed));

    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        MODEL = glm::translate(MODEL, glm::vec3(1 * movementSpeed, 0 * movementSpeed, 0 * movementSpeed));

    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        MODEL = glm::rotate(MODEL, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));

    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        MODEL = glm::rotate(MODEL, -0.1f, glm::vec3(0.0f, 1.0f, 0.0f));

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        MODEL = glm::translate(MODEL, glm::vec3(0 * movementSpeed, 1 * movementSpeed, 0 * movementSpeed));

    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        MODEL = glm::translate(MODEL, glm::vec3(0 * movementSpeed, -1 * movementSpeed, 0 * movementSpeed));

    if (key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        FoV += 2.0f;
        recalculateProjection();
    }
    if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        FoV -= 2.0f;
        recalculateProjection();
    }
}
double last_mouse_pos_x = 0;

// mouse event callback
void cursor(GLFWwindow *window, double x, double y)
{
    float angle = (x - last_mouse_pos_x) / 1000;
    last_mouse_pos_x = x;

    MODEL = glm::rotate(MODEL, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    //MODEL = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

// Resize event callback
void resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    AspectRatio = width / (float)height;

    recalculateProjection();
}
