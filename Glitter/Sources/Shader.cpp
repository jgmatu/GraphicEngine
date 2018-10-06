#include "Shader.hpp"

Shader::Shader() {
      programId = glCreateProgram();

      if (programId == 0) {
            std::cerr << "Shader failed" << std::endl;
      }
      vertexShaderId = 0;
      fragmentShaderId = 0;
}

Shader::~Shader() {
      ;
}

void
Shader::createVertexShader(const std::string& sc) {
      this->vertexName = sc;
      vertexShaderId = createShader(sc, GL_VERTEX_SHADER);
}

void
Shader::createFragmentShader(const std::string& sc) {
      this->fragmentName = sc;
      vertexShaderId = createShader(sc, GL_FRAGMENT_SHADER);
}

void
Shader::bind() { glUseProgram(programId); }

void
Shader::unbind() { glUseProgram(0); }

void
Shader::cleanup() {
      unbind();
      if (programId != 0) {
            glDeleteProgram(programId);
      }
}

void
Shader::createUniform(std::string uniformName) {
      int uniformLocation = glGetUniformLocation(programId, uniformName.c_str());

      if (uniformLocation < 0) {
            std::cerr << "Could not find uniform: " << uniformName  <<
            std::endl <<  "Value : " << uniformLocation << std::endl;
            std::cerr << vertexName << '\n';
            std::cerr << fragmentName << '\n';
            throw;
      }
      uniforms.insert(std::pair<std::string, int>(uniformName, uniformLocation));
}

void
Shader::setUniform(std::string name, glm::vec3 value) {
      glUniform3f(uniforms[name], value.x, value.y, value.z);
}

void
Shader::setUniform(std::string name, glm::mat4 matrix) {
      glUniformMatrix4fv(uniforms[name], 1, GL_FALSE,  glm::value_ptr(matrix));
}

void
Shader::setUniform(std::string name, int value) {
      glUniform1i(uniforms[name], value);
}

int
Shader::createShader(const std::string& sc, int shaderType) {
    int params;

    const char* _sc = sc.c_str();
    int size = sc.size();

    int shaderId = glCreateShader(shaderType);
    if (shaderId == 0) {
        std::cerr << "Error creating shader. Type: " << shaderType << '\n';
        std::cerr << vertexName << '\n';
        std::cerr << fragmentName << '\n';
    }
    glShaderSource(shaderId, 1, &_sc, &size);
    glCompileShader(shaderId);

    int InfoLogLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &params);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stderr, "Vertex Shader Error Message: %s\n", &VertexShaderErrorMessage[0]);
    }
    glAttachShader(programId, shaderId);
    return shaderId;
}

void
Shader::link() {
      int params;
      char inflog[1024];
      int size;

      glLinkProgram(programId);
      glGetProgramiv(programId, GL_LINK_STATUS, &params);
      if (!params) {
            glGetProgramInfoLog(programId, 1024, &size, inflog);
            std::cerr << vertexName << '\n';
            std::cerr << fragmentName << '\n';
            std::cerr << "Error linking Shader code: " << inflog << std::endl;
            throw;
      }

      if (vertexShaderId != 0) {
            glDetachShader(programId, vertexShaderId);
      }

      if (fragmentShaderId != 0) {
            glDetachShader(programId, fragmentShaderId);
      }

      glValidateProgram(programId);
      glGetProgramiv(programId, GL_LINK_STATUS, &params);

      if (!params) {
            glGetProgramInfoLog(programId, 1024, &size, inflog);
            std::cerr << vertexName << '\n';
            std::cerr << fragmentName << '\n';
            std::cerr << "Error linking Shader code: " << inflog << std::endl;
            throw;
      }
}
