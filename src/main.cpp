#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

#include "globals.h"
#include "callbacks.h"
#include "renderLoop.h"
#include "shaders.h"
#include "objLoader.h"

GLuint vertexArray, vertexBuffer;

int Initialize(GLFWwindow *&window, GLuint &shaderProgramID, size_t &vertexCount)
{
    // Check GLFW initialization
    if (!glfwInit())
    {
        std::cout << "Cannot initialize GLFW." << std::endl;
        return -1;
    }

    // initialize OpenGL context (ver 3.3, profile core, with 16 samples (AntiAliasing))
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 16);

    // Create window 800x600
    window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);

    // Check if cannot create window
    if (window == nullptr)
    {
        glfwTerminate();

        std::cout << "Cannot create window." << std::endl;
        return -1;
    }

    // Register event callbacks
    //      resize window callback
    glfwSetFramebufferSizeCallback(window, resize);
    //      keyboard callback
    glfwSetKeyCallback(window, keyboard);
    //      Mouse callback
    glfwSetCursorPosCallback(window, cursor);

    // Setup window context (tell OpenGL to render on the created window)
    glfwMakeContextCurrent(window);

    // Check if can load OpenGL procedures (carrega as funcoes do OpenGL disponiveis)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();

        std::cout << "Cannot load OpenGL procedures." << std::endl;
        return -1;
    }

    // Check if can create shader program
    if (!createProgram("../res/shaders/triangle", shaderProgramID))
    {
        glfwTerminate();

        std::cout << "Cannot create shader program." << std::endl;
        return -1;
    }

    // Use shader program
    glUseProgram(shaderProgramID);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Read triangle mesh from Wavefront OBJ file format
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<size_t> positionIndices;
    std::vector<size_t> normalIndices;
    std::vector<size_t> textureCoordinateIndices;

    readTriangleMesh(
        //"../res/meshes/tetrahedron.obj",
        //"../res/meshes/obj.obj",
        "../res/meshes/bunny.obj",
        positions,
        normals,
        textureCoordinates,
        positionIndices,
        normalIndices,
        textureCoordinateIndices);

    // Load triangle mesh to OpenGL

    vertexCount = loadTriangleMesh(
        positions,
        normals,
        textureCoordinates,
        positionIndices,
        normalIndices,
        textureCoordinateIndices,
        GL_STATIC_DRAW,
        vertexArray,
        vertexBuffer);

    // Setup view matrix
    view_matrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 10.0f),
        glm::vec3(0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    // Initialize projection matrix and viewport
    resize(window, 800, 600);

    return 0;
}

void Deinitialize(GLFWwindow *window, GLuint &shaderProgramID)
{

    // Delete shader program
    glDeleteProgram(shaderProgramID);

    // Delete vertex array object
    glDeleteVertexArrays(1, &vertexArray);

    // Delete vertex buffer object
    glDeleteBuffers(1, &vertexBuffer);

    // Destroy window
    glfwDestroyWindow(window);

    // Deinitialize GLFW
    glfwTerminate();
}

int main(int argc, char **argv)
{
#pragma region usage
    /* GLM usage
    
    glm::vec3 u(1.0f, 0, 0);
    glm::vec3 v(0, 1.0f, 0);
    
    glm::vec3 d = glm::dot(u, v);
    
    glm::mat3 m(0.0f, 1.0f, 2.0f,  // First column
    			   3.0f, 4.0f, 5.0f,  // Second column
    			   6.0f, 7.0f, 8.0f); // Third column
    
    Print GLM matrix
    std::cout << glm::to_string(m) << std::endl;
    
    Access the first column as GLM vector
    std::cout << glm::to_string(m[0]) << std::endl;
    
    Access the second element of the first column as float
    std::cout << m[0][1] << std::endl;

    Access vertex position attributes of the first triangle
    
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<size_t> positionIndices;
    std::vector<size_t> normalIndices;
    std::vector<size_t> textureCoordinateIndices;

    if (loadTriangleMesh(
            "../res/meshes/bunny.obj",
            positions, normals, textureCoordinates,
            positionIndices, normalIndices, textureCoordinateIndices)) {
    	   size_t triangleIndex = 0;
    
    	   glm::vec3 p0 = positions[positionIndices[triangleIndex * 3]];
    	   glm::vec3 p1 = positions[positionIndices[triangleIndex * 3 + 1]];
    	   glm::vec3 p2 = positions[positionIndices[triangleIndex * 3 + 2]];
    
    	   std::cout << "First triangle vertices: " << std::endl;
    
    	   std::cout << glm::to_string(p0) << std::endl;
    	   std::cout << glm::to_string(p1) << std::endl;
        std::cout << glm::to_string(p2) << std::endl;
    } */
#pragma endregion

    // Shader program ID
    GLuint shaderProgramID;

    std::cout << "Initializing... " << std::endl;

    // GLFW window
    GLFWwindow *window;
    size_t vertexCount;
    auto initializationResult = Initialize(window, shaderProgramID, vertexCount);
    if (initializationResult != 0)
    {
        int t;
        std::cout << "Enter to continue\n";
        std::cin >> t;
        return initializationResult;
    }

    // Render loop
    std::cout << "Starting render loop." << std::endl;

    RenderLoop(window, shaderProgramID, vertexCount);

    // Deinitialize everything after rendering stops
    std::cout << "Deinitializing." << std::endl;
    Deinitialize(window, shaderProgramID);

    return 0;
}
