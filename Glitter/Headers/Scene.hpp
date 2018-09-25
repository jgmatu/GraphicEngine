#ifndef SCENE_H
#define SCENE_H

#include <map>

#include "Camera.hpp"
#include "Component.hpp"

class Scene {

public:

    Scene();
    ~Scene();

    void setup();

    void init();
    void render();

    void add(Component *component);

private:

    void demo(float angle);

    void setup_cubes();
    void setup_spheres();

    Camera *_camera;
    GLFWwindow *_window;

    unsigned int _ncomponent;
    std::map<unsigned, Component*> _components;

};

#endif
