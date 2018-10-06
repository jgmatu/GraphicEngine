#include "Component.hpp"
#include <stb_image.h>

Component::Component(Camera *camera) {
    _shader = new Shader();
    _tf = new Transform();
    _camera = camera;
}

Component::~Component() {
    delete _shader;
}

void Component::vertexArrayID() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

std::string Component::getDataFile(const std::string& filename) {
   std::ifstream file(filename);

   file.open("r");
   if (!file.is_open()) {
       std::cerr << "Error opening file..." << std::endl;
   }
   std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
   file.close();
   return data;
}

void Component::loadTexture(const char *filename) {
    int width, heigth, channels;
    unsigned char* pixels = stbi_load (filename, &width, &heigth, &channels, 0);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID); // all upcoming GL_TEXTURE_2D operations now have

    // set the texture wrapping parameters.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(pixels);
}

void Component::genVertexBufferPosition() {
    // Position attribute...
    glGenBuffers(1, &VBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind Vertex VAO...
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexPos.size() * 3, _vertexPos.data(), GL_STATIC_DRAW); // Assign buffer to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
}

void Component::genVertexBufferNormal() {
    // Normal attribute...
    glGenBuffers(1, &VBO2); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexNormal.size() * 3, _vertexNormal.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);
}

void Component::genVertexBufferTextCoord() {
    // Text Coord attribute...
    glGenBuffers(1, &VBO3); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexTexCoord.size() * 2, _vertexTexCoord.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(2);
}

void Component::genVertexBufferIndex() {
    // Buffer indexes...
    glGenBuffers(1, &EBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _NTriangleIndex * sizeof(GL_UNSIGNED_INT) * 3, _triangleIndex.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO.
    glBindVertexArray(0); // Unbind the VAO.
}

void Component::shader() {
    _shader->createVertexShader(getDataFile(_vertex));
    _shader->createFragmentShader(getDataFile(_fragment));
    _shader->link();
    _programID = _shader->getProgramId();
}

void Component::draw() {
    // 1st attribute buffer : vertices
    glBindVertexArray(VAO); // Activa la geometría que se va a pintar.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Activar el buffer de vertices a pintar.
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    // Draw the cube!
    glDrawElements(GL_TRIANGLES, _NTriangleIndex * 3, GL_UNSIGNED_INT, 0);
}

void Component::texture() {
    glActiveTexture(GL_TEXTURE0); // Activate first texture unit
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Component::bind() {
    glUseProgram(_programID);
}

void Component::start() {
    this->vertexArrayID();
    this->genVertexBufferPosition();
    this->genVertexBufferNormal();
    this->genVertexBufferTextCoord();
    this->genVertexBufferIndex();
    this->shader();

    this->createUniform("projection");
    this->createUniform("view");
    this->createUniform("model");
    this->createUniform("diffuseTexture");
}

static GLint64 getTime() {
    GLint64 timer;

    glGetInteger64v(GL_TIMESTAMP, &timer);
    return timer;
}

static float getAngle() {
    return std::fmod((getTime() / 1000000000.0), (2.0f * M_PI));
}

void Component::awakeStart() {
    _tf->translate(glm::vec3(_tf->_x, _tf->_y, _tf->_z));
    _tf->rotate(getAngle(), glm::vec3(1.0f, -1.0f, 0.0f));

    this->setUniform("projection", _camera->_projection);
    this->setUniform("view", _camera->_view);
    this->setUniform("model", _tf->model());
    this->setUniform("diffuseTexture", 0); // El índice es el mismo que en glActiveTexture()

    // Render...
    this->bind();
    this->texture();
    this->draw();
}

void Component::update() {
    this->_tf->identity();
    this->_tf->move();
}
