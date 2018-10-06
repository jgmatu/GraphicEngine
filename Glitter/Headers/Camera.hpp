#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

class Camera {

public:

    Camera();
    ~Camera();

    glm::mat4 _view;
    glm::mat4 _projection;

private:

    const float aspectRatio = 4.0f / 3.0f;

};

#endif
