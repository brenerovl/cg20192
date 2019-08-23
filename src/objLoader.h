#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

bool readTriangleMesh(
    const std::string &filename,
    std::vector<glm::vec3> &positions,
    std::vector<glm::vec3> &normals,
    std::vector<glm::vec2> &textureCoordinates,
    std::vector<size_t> &positionIndices,
    std::vector<size_t> &normalIndices,
    std::vector<size_t> &textureCoordinateIndices);

size_t loadTriangleMesh(
    const std::vector<glm::vec3> &positions,
    const std::vector<glm::vec3> &normals,
    const std::vector<glm::vec2> &textureCoordinates,
    const std::vector<size_t> &positionIndices,
    const std::vector<size_t> &normalIndices,
    const std::vector<size_t> &textureCoordinateIndices,
    GLenum usage,
    GLuint &vao,
    GLuint &vbo);

#endif