#include <glad/glad.h>

#include "objLoader.h"
#include <glm/vec3.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

// Read triangle mesh from Wavefront OBJ file format
bool readTriangleMesh(
    const std::string &filename,
    std::vector<glm::vec3> &positions,
    std::vector<glm::vec3> &normals,
    std::vector<glm::vec2> &textureCoordinates,
    std::vector<size_t> &positionIndices,
    std::vector<size_t> &normalIndices,
    std::vector<size_t> &textureCoordinateIndices)
{
    std::ifstream file(filename, std::ifstream::in);

    if (!file.is_open())
        return false;

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream attributes(line);

        std::string type;
        attributes >> type;

        if (type == "v")
        {
            glm::vec3 position;
            attributes >> position.x >> position.y >> position.z;

            positions.push_back(position);
        }
        else if (type == "vt")
        {
            glm::vec2 textureCoordinate;
            attributes >> textureCoordinate.x >> textureCoordinate.y;

            textureCoordinates.push_back(textureCoordinate);
        }
        else if (type == "vn")
        {
            glm::vec3 normal;
            attributes >> normal.x >> normal.y >> normal.z;

            normals.push_back(normal);
        }
        else if (type == "f")
        {
            for (size_t i = 0; i < 3; i++)
            {
                std::string tokens;
                attributes >> tokens;

                std::replace(tokens.begin(), tokens.end(), '/', ' ');

                std::istringstream indices(tokens);
                size_t index;

                indices >> index;
                positionIndices.push_back(index - 1);

                if (indices.peek() == ' ')
                {
                    indices.ignore();

                    if (indices.peek() == ' ')
                    {
                        indices.ignore();

                        indices >> index;
                        normalIndices.push_back(index - 1);
                    }
                    else
                    {
                        indices >> index;
                        textureCoordinateIndices.push_back(index - 1);

                        if (indices.peek() == ' ')
                        {
                            indices.ignore();

                            indices >> index;
                            normalIndices.push_back(index - 1);
                        }
                    }
                }
            }
        }
    }

    file.close();

    return true;
}

// EXERC�CIO
//
// IMPLEMENTAR A FUN��O ABAIXO VALENDO 10 PONTOS EXTRAS.
// ATUALMENTE ELA N�O UTILIZA OS PAR�METROS DE ENTRADA E
// CARREGA UM TRI�NGULO CONSTANTE COM ATRIBUTOS DE POSI��O E COR.
// O OBJETIVO � MODIFIC�-LA PARA CARREGAR OS TRI�NGULOS DESCRITOS
// PELOS PAR�METROS, SEGUINDO A SUA DOCUMENTA��O:
//
// Load triangle mesh to OpenGL
// Normal and texture coordinate attributes are calculated by primitive when not available
// Vertex attributes are exported to shader program at locations:
// 0: position
// 1: normal
// 2: texture coordinate
size_t loadTriangleMesh(
    const std::vector<glm::vec3> &positions,
    const std::vector<glm::vec3> &normals,
    const std::vector<glm::vec2> &textureCoordinates,
    const std::vector<size_t> &positionIndices,
    const std::vector<size_t> &normalIndices,
    const std::vector<size_t> &textureCoordinateIndices,
    GLenum usage,
    GLuint &vertexArray,
    GLuint &vertexBuffer)
{

    //std::cout << "Indices: " << positionIndices.size();
    GLfloat vertices[positionIndices.size() * 2 * 3];
    for (size_t i = 0; i < positionIndices.size() / 3; i++)
    {
        //std::cout << "\nF(" << i << ") = \n";
        for (size_t j = 0; j < 3; j++)
        {
            auto posIndex = positionIndices[i * 3 + j];
            auto normIndex = normalIndices[i * 3 + j];
            //std::cout << " " << posIndex;
            //std::cout << "    vert: ";
            for (int k = 0; k < 3; k++)
            {
                auto idx = 18 * i + 6 * j + k;
                vertices[idx] = positions[posIndex][k];
                //std::cout << " (" << (idx) << ")" << vertices[idx];
            }
            //std::cout << "\n    norm: ";
            for (int k = 0; k < 3; k++)
            {
                auto idx = 18 * i + 6 * j + k + 3;
                vertices[idx] = normals[normIndex][k];
                //std::cout << " (" << (idx) << ")" << vertices[idx];
            }
            //std::cout << "\n\n";
        }
    }
    //std::cout << std::endl;
    // Triangle description
    /*  GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // First vertex position
         1.0f,  0.0f, 0.0f, // First vertex color
         
         0.5f, -0.5f, 0.0f, // Second vertex position
         0.0f,  1.0f, 0.0f, // Second vertex color
         
         0.0f,  0.5f, 0.0f, // Third vertex position
         0.0f,  0.0f, 1.0f, // Third vertex color
    }; */
    /* GLfloat vertices[] = {
        // triangle (face) 0
        1.0f, 0.0f, 0.0f, // v3, vertex 0
        0.0f, 1.0f, 0.0f, // normal 0 (represented as color in the triangle)

        0.0f, 1.0f, 0.0f, // v2, vertex 1
        0.0f, 1.0f, 0.0f, // normal 0 (represented as color in the triangle)

        0.0f, 0.0f, 0.0f, // v1, vertex 2
        0.0f, 1.0f, 0.0f, // normal 0 (represented as color in the triangle)

        // triangle (face) 1
        0.0f, 0.0f, 1.0f, // v0, vertex 0
        0.0f, 1.0f, 0.0f, // normal 0 (represented as color in the triangle)

        1.0f, 0.0f, 0.0f, // v3, vertex 1
        0.0f, 1.0f, 0.0f, // normal 0 (represented as color in the triangle)

        0.0f, 0.0f, 0.0f, // v1, vertex 2
        0.0f, 1.0f, 0.0f, // normal 0 (represented as color in the triangle)
    }; */

    // Create and bind vertex array object (alocando 1 vertex array)
    glGenVertexArrays(1, &vertexArray);

    // pra dizer pro gl pra usar o vertex array vinculado
    glBindVertexArray(vertexArray);

    // Create and bind vertex buffer object
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Copy vertex attribute data to vertex buffer object
    glBufferData(
        GL_ARRAY_BUFFER, // mesmo usado acima
        sizeof(vertices),
        vertices,
        usage);

    // Define position attribute to shader program
    glVertexAttribPointer(
        0, // slot (id do atributo)
        3, // size of attrib (qt de componentes do param)
        GL_FLOAT,
        false,                    // normalize?
        6 * sizeof(GLfloat),      // stride: quantos floats precisa pra representar um vertice * tamanho do tipo do dado
        (const GLvoid *)nullptr); // begining
    //(const GLvoid *)0); // same thing as (const GLvoid *)nullptr);

    // [x, y, z, nx ,ny, nz][x, y, z, nx ,ny, nz]
    // |------vertex 0-----||------vertex 1-----|

    // Enable position attribute to shader program (id 0)
    glEnableVertexAttribArray(0);

    // Define normal attribute to shader program
    glVertexAttribPointer(
        1,                                      // id pro attrib
        3,                                      // tem 3 floats
        GL_FLOAT,                               // do tipo float
        false,                                  // n precisa normalizar (foi normalizado pelo obj)
        6 * sizeof(GLfloat),                    // começa a repetir a partir do 6 elemento (em bytes)
        (const GLvoid *)(3 * sizeof(GLfloat))); // começa no 3ro elemento

    // Enable color (normal?) attribute to shader program (id 1)
    glEnableVertexAttribArray(1);

    // Return vertex count or three times the triangle count
    return positionIndices.size();
}