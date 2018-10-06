#ifndef SCENE_H
#define SCENE_H

#include <map>

#include "Camera.hpp"
#include "Component.hpp"
#include "Visitor.hpp"

class Scene {

public:

    Scene();
    ~Scene();

    void setup();

    void init();
    void render();

    void add(Component *component);

private:

    void demo();

    void demo_visitor();

    void setup_cubes();
    void setup_spheres();
    void setup_visitor();

    Camera *_camera;
    GLFWwindow *_window;

    unsigned int _ncomponent;
    std::map<unsigned, Component*> _components;

};

#endif
