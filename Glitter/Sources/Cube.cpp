#include "Cube.hpp"
#include <stb_image.h>


Cube::Cube() {
    _shader = new ShaderProgram();
    _model = glm::mat4(1);
}

std::string Cube::getDataFile(const std::string& filename) {
   std::ifstream file(filename);

   file.open("r");
   if (!file.is_open()) {
       std::cerr << "Error opening file..." << std::endl;
   }
   std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
   file.close();
   return data;
}


void Cube::vertexArrayID() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void Cube::genVertexBuffer() {

    // Position attribute...
    glGenBuffers(1, &VBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind Vertex VAO...
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexPos) * 3, cubeVertexPos, GL_STATIC_DRAW); // Assign buffer to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    // Normal attribute...
    glGenBuffers(1, &VBO2); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexNormal) * 3, cubeVertexNormal, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    // Text Coord attribute...
    glGenBuffers(1, &VBO3); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexTexCoord) * 2, cubeVertexTexCoord, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(2);

    // Buffer indexes...
    glGenBuffers(1, &EBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeNTriangleIndex * sizeof(GL_UNSIGNED_INT) * 3, cubeTriangleIndex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO.
    glBindVertexArray(0); // Unbind the VAO.
}

void Cube::createUniform(std::string name) {
    _shader->createUniform(name);
}

void Cube::setUniform(std::string name, glm::mat4 mat4) {
    _shader->setUniform(name, mat4);
}

void Cube::shader() {
    _shader->createVertexShader(getDataFile("./Glitter/GLSL/cube/vertex.glsl"));
    _shader->createFragmentShader(getDataFile("./Glitter/GLSL/cube/fragment.glsl"));
    _shader->link();

    _programID = _shader->getProgramId();
}

void Cube::loadTexutre(const char *filename) {
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

void Cube::texture() {
    glActiveTexture(GL_TEXTURE0); // Activate first texture unit
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void
Cube::setUniform(std::string name, int value) {
      _shader->setUniform(name, value);
}

void Cube::draw() {
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
    glDrawElements(GL_TRIANGLES, cubeNTriangleIndex * 3, GL_UNSIGNED_INT, 0);
}

// Ejecutar el programa de shaders del objeto ya compilado...
void Cube::bind() {
    glUseProgram(_programID);
}

void Cube::identity() {
    _model = glm::mat4(1.0);
}

void Cube::translate(glm::vec3 vec3) {
    _model *= glm::translate(_model, vec3);
}

void Cube::scale(glm::vec3 vec3) {
    _model *= glm::scale(_model, vec3);
}

void Cube::rotate(float angle, glm::vec3 direction) {
    _model *= glm::rotate(angle, direction);
}
