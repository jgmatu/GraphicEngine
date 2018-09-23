#include "Cube.hpp"


Cube::Cube() {
    ;
}

std::string Cube::getDataFile(const std::string& filename)
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


void Cube::vertexArrayID() {
    glGenVertexArrays(1, &_vertexArrayID);
    glBindVertexArray(_vertexArrayID);
}

void Cube::genVertexBuffer() {
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}


void Cube::shader() {
    ShaderProgram* shader = new ShaderProgram();

    shader->createVertexShader(getDataFile("./Glitter/GLSL/cube/vertex.glsl"));
    shader->createFragmentShader(getDataFile("./Glitter/GLSL/cube/fragment.glsl"));
    shader->link();

    _programID = shader->getProgramId();
}


void Cube::draw() {
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
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 * 3 los índices comienzan en 0 -> 12 triángulos -> 6 cuadrados.
    glDisableVertexAttribArray(0);
}

void Cube::bind() {
    glUseProgram(_programID);
}
