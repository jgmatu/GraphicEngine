#ifndef TRIANGLE_H
#define TRIANGLE_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "ShaderProgram.hpp"

class Triangle {

public:

    Triangle();
    ~Triangle();

    void vertexArrayID();
    void genVertexBuffer();

    void draw();
    void bind();

    void shader();

    void createUniform(std::string name);
    void setUniform(std::string name, glm::mat4 mat4);

    void identity();
    void translate(glm::vec3 vec3);
    void scale(glm::vec3 vec3);

    glm::mat4 _model;

private:

    std::string getDataFile(const std::string& filename);

    GLuint _vertexArrayID;
    // This will identify our vertex buffer
    GLuint _vertexbuffer;
    GLuint _programID;

    ShaderProgram* _shader;

    // An array of 3 vectors which represents 3 vertices
    const GLfloat g_vertex_buffer_data[3 * 3] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
};

#endif
