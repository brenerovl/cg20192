
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "renderLoop.h"
#include "globals.h"

void RenderLoop(GLFWwindow *&window, GLuint shaderProgramID, size_t vertexCount)
{
    while (!glfwWindowShouldClose(window))
    {
        // Setup color buffer ('clears' [fills] the buffer with the specified color)
        if (BACKGROUND_STATE)
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        else
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear color buffer (executes the glClearColor)
        glClear(GL_COLOR_BUFFER_BIT);

        // Setup depth buffer
        glClearDepth(1.0f);

        // Clear depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        // Could also clear both with: glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Pass model matrix as parameter to shader program
        GLint modelLocationID = glGetUniformLocation(shaderProgramID, "model");
        glUniformMatrix4fv(modelLocationID, 1, GL_FALSE, glm::value_ptr(MODEL));

        // Pass view matrix as parameter to shader program
        GLint viewLocationID = glGetUniformLocation(shaderProgramID, "view");
        glUniformMatrix4fv(viewLocationID, 1, GL_FALSE, glm::value_ptr(view_matrix));

        // Pass projection matrix as parameter to shader program
        GLint projectionLocationID = glGetUniformLocation(shaderProgramID, "projection");
        glUniformMatrix4fv(projectionLocationID, 1, GL_FALSE, glm::value_ptr(PROJECTION));

        // Draw vertex array as triangles, starting at vertex 0 and amount of vertices (vertexCount)
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        // Swap double buffer
        glfwSwapBuffers(window);

        // Process events and callbacks
        glfwPollEvents();

        if (KillWindow)
            glfwSetWindowShouldClose(window, true);
    }
}
