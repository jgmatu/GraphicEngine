#include "Triangle.hpp"


Triangle::Triangle() {
    _shader = new ShaderProgram();
}

Triangle::~Triangle() {
    ;
}

std::string Triangle::getDataFile(const std::string& filename)
{
   std::ifstream file(filename);

   file.open("r");
   if (!file.is_open()) {
       std::cerr << "Error opening file..." << std::endl;
   }
   std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
   file.close();
   return data;
}


void Triangle::vertexArrayID()
{
    glGenVertexArrays(1, &_vertexArrayID);
    glBindVertexArray(_vertexArrayID);
}

void Triangle::genVertexBuffer()
{
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}


void Triangle::createUniform(std::string name) {
    _shader->createUniform(name);
}

void Triangle::setUniform(std::string name, glm::mat4 mat4) {
    _shader->setUniform(name, mat4);
}

void Triangle::shader()
{
    _shader->createVertexShader(getDataFile("./Glitter/GLSL/triangle/vertex.glsl"));
    _shader->createFragmentShader(getDataFile("./Glitter/GLSL/triangle/fragment.glsl"));
    _shader->link();

    _programID = _shader->getProgramId();
}


void Triangle::draw() {
        // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void Triangle::bind()  {
    glUseProgram(_programID);
}
