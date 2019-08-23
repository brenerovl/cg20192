#include <glad/glad.h>
#include "shaders.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <sstream>
#include <fstream>
#include <iostream>


// Compile shader source code from text file format
bool compileShader(const std::string &filename, GLenum type, GLuint &id)
{
    // Read from text file to string
    std::ifstream file(filename, std::ifstream::in);

    if (!file.is_open())
        return false;

    std::stringstream buffer;
    std::string source;

    buffer << file.rdbuf();
    source = buffer.str();

    // Create shader
    GLuint shaderID = glCreateShader(type);

    // Setup shader source code
    const GLchar *src = source.data();
    glShaderSource(shaderID, 1, &src, nullptr);

    // Compile shader
    glCompileShader(shaderID);

    // Get compilation status
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

    // Check compilation errors
    if (status != GL_TRUE)
    {
        // Get log message size of the compilation process
        GLint size = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &size);

        std::string message;
        message.resize(size);

        // Get log message of the compilation process
        glGetShaderInfoLog(shaderID, size, nullptr, (GLchar *)message.data());

        // Print log message
        std::cout << message << std::endl;

        // Delete shader
        glDeleteShader(shaderID);

        return false;
    }

    // Return shader id
    id = shaderID;

    return true;
}

// Create shader program
bool createProgram(const std::string &name, GLuint &id)
{
    GLuint vertexShaderID, fragmentShaderID;

    // Load and compile vertex shader
    if (!compileShader(name + ".vert", GL_VERTEX_SHADER, vertexShaderID))
        return false;

    // Load and compile fragment shader
    if (!compileShader(name + ".frag", GL_FRAGMENT_SHADER, fragmentShaderID))
        return false;

    // Create shader program
    GLuint shaderProgramID = glCreateProgram();

    // Attach compiled shaders to program
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);

    // Link attached shaders to create an executable
    glLinkProgram(shaderProgramID);

    // Delete compiled shaders, the program is already linked
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    // Get linkage status
    GLint status;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);

    // Check linkage errors
    if (status != GL_TRUE)
    {
        // Get log message size of the linkage process
        GLint size = 0;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &size);

        std::string message;
        message.resize(size);

        // Get log message of the linkage process
        glGetProgramInfoLog(shaderProgramID, size, nullptr, (GLchar *)message.data());

        // Print log message
        std::cout << message << std::endl;

        // Delete shader program
        glDeleteProgram(shaderProgramID);

        return false;
    }

    // Return shader program id
    id = shaderProgramID;

    return true;
}