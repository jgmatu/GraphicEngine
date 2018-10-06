#ifndef TRANSFORM_H
#define TRANSFORM_H


#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

class Transform {

public:

    Transform();
    ~Transform();

    void identity();
    void translate(glm::vec3 vec3);
    void scale(glm::vec3 vec3);
    void rotate(float angle, glm::vec3 direction);
    glm::mat4 model();
    void move();

    float _x, _y, _z;

private:

    glm::mat4 _model;

};

#endif
