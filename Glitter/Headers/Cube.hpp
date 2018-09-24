#ifndef CUBE_H
#define CUBE_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "ShaderProgram.hpp"
#include "BOX.h"

class Cube {
public:

    Cube();
    ~Cube();

    void vertexArrayID();
    void genVertexBuffer();

    void draw();
    void bind();

    void shader();

    void createUniform(std::string name);
    void setUniform(std::string name, glm::mat4 mat4);
    void setUniform(std::string name, int value);

    void identity();
    void translate(glm::vec3 vec3);
    void scale(glm::vec3 vec3);
    void rotate(float angle, glm::vec3 direction);
    void texture();
    void loadTexutre(const char *texture);

    glm::mat4 _model;

private:

    std::string getDataFile(const std::string& filename);

    GLuint VAO;
    // This will identify our vertex buffer
    GLuint _programID, _textureID;

    GLuint VBO, VBO2, VBO3 ,EBO;

    ShaderProgram *_shader;
};

#endif
