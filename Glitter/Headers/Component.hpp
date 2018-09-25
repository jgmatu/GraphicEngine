#ifndef COMPONENT_H
#define COMPONENT_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "ShaderProgram.hpp"

class Component {

public:

    Component();
    ~Component();

    void setVertexPos(std::vector<GLfloat> vertexPos) {
        this->_vertexPos = vertexPos;
    };

    void setVertexNormal(std::vector<GLfloat> vertexNormal) {
        this->_vertexNormal = vertexNormal;
    };

    void setVertexTexCoord(std::vector<GLfloat> vertexTexCoord) {
        this->_vertexTexCoord = vertexTexCoord;
    };

    void setTriangleIndex(std::vector<GLuint> triangleIndex, unsigned NTriangleIndex) {
        this->_triangleIndex = triangleIndex;
        this->_NTriangleIndex = NTriangleIndex;
    };

    void vertexArrayID();

    void genVertexBufferPosition();
    void genVertexBufferNormal();
    void genVertexBufferTextCoord();
    void genVertexBufferIndex();

    void loadTexture(const char *filename);

    void draw();
    void bind();

    void shader(std::string vertex, std::string fragment);
    void texture();

    void createUniform(std::string name) {
        _shader->createUniform(name);
    }

    void setUniform(std::string name, glm::mat4 mat4) {
        _shader->setUniform(name, mat4);
    }

    void setUniform(std::string name, int value) {
        _shader->setUniform(name, value);
    }

    glm::mat4 _model;

    void identity() {
        _model = glm::mat4(1.0);
    }

    void translate(glm::vec3 vec3) {
        _model *= glm::translate(_model, vec3);
    }

    void scale(glm::vec3 vec3) {
        _model *= glm::scale(_model, vec3);
    }

    void rotate(float angle, glm::vec3 direction) {
        _model *= glm::rotate(angle, direction);
    }

protected:

    std::string getDataFile(const std::string& filename);

    // Active Buffer.
    GLuint VAO;

    // This will identify our vertex buffer
    GLuint _programID, _textureID;

    // Vertices Buffers...
    GLuint VBO, VBO2, VBO3, EBO;

    ShaderProgram *_shader;

    std::vector<GLfloat> _vertexPos;
    std::vector<GLfloat> _vertexNormal;
    std::vector<GLfloat> _vertexTexCoord;
    std::vector<GLuint> _triangleIndex;
    int _NTriangleIndex;

};

#endif
