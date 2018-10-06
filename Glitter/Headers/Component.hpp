#ifndef COMPONENT_H
#define COMPONENT_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Element.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

class Component: public Element {

public:

    Component(Camera *camera);
    ~Component();

    void setVertexPos(const std::vector<GLfloat> vertexPos) {
        this->_vertexPos = vertexPos;
    };

    void setVertexNormal(const std::vector<GLfloat> vertexNormal) {
        this->_vertexNormal = vertexNormal;
    };

    void setVertexTexCoord(const std::vector<GLfloat> vertexTexCoord) {
        this->_vertexTexCoord = vertexTexCoord;
    };

    void setTriangleIndex(const std::vector<GLuint> triangleIndex, const unsigned NTriangleIndex) {
        this->_triangleIndex = triangleIndex;
        this->_NTriangleIndex = NTriangleIndex;
    };

    void loadTexture(const char *filename);

    void shader(std::string vertex, std::string fragment) {
        this->_vertex = vertex;
        this->_fragment = fragment;
    };

    // Metodo para empezar con el patrón de diseño
    void accept(class Visitor &v);

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart();

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start();

    // Método que realiza transformaciones, cálculos de cosas.
    void update();

    Transform *_tf;

private:

    void vertexArrayID();
    void genVertexBufferPosition();
    void genVertexBufferNormal();
    void genVertexBufferTextCoord();
    void genVertexBufferIndex();

    void shader();
    void texture();

    void bind();
    void draw();

    void createUniform(std::string name) {
        _shader->createUniform(name);
    }

    void setUniform(std::string name, glm::mat4 mat4) {
        _shader->setUniform(name, mat4);
    }

    void setUniform(std::string name, int value) {
        _shader->setUniform(name, value);
    }

    std::string getDataFile(const std::string& filename);

    // Active Buffer.
    GLuint VAO;

    // This will identify our vertex buffer
    GLuint _programID, _textureID;

    // Vertices Buffers...
    GLuint VBO, VBO2, VBO3, EBO;

    std::vector<GLfloat> _vertexPos;
    std::vector<GLfloat> _vertexNormal;
    std::vector<GLfloat> _vertexTexCoord;
    std::vector<GLuint> _triangleIndex;
    int _NTriangleIndex;

    std::string _vertex;
    std::string _fragment;

    Shader *_shader;
    Camera *_camera;
};

#endif
