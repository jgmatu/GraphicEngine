#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <vector>
#include <iostream>
#include <map>


class Shader {

public:

    Shader();
    ~Shader();
    void createVertexShader(const std::string& sc);
    void createFragmentShader(const std::string& sc);
    void link();
    void bind();
    void unbind();
    void cleanup();

    void createUniform(std::string uniformName);
    void setUniform(std::string name, glm::vec3 value);
    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, int value);

    GLuint getProgramId() { return programId; };

protected:

    int createShader(const std::string& sc, int shaderType);

private:

    GLuint programId;
    GLuint vertexShaderId;
    GLuint fragmentShaderId;

    std::map<std::string, int> uniforms;

    std::string vertexName;
    std::string fragmentName;

};

#endif
