#include "Scene.hpp"
#include "BOX.h"
#include "Sphere.hpp"

Scene::Scene() : _ncomponent(0), _components() {
    _camera = new Camera();
}

Scene::~Scene() {
    ;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << scancode << " " << mods << std::endl;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Scene::add(Component *component) {
    _components.insert(std::pair<const unsigned int, Component*>(_ncomponent++, component));
}

void Scene::setup_visitor() {
    Sphere *buffer = new Sphere();
    buffer->createBuffer();

    for (unsigned i = 0; i < 3; ++i) {
        Component *c = new Component(_camera);

        c->setVertexPos(buffer->getPosVertex());
        c->setVertexNormal(buffer->getNormals());
        c->setVertexTexCoord(buffer->getTexCoords());
        c->setTriangleIndex(buffer->getIndexes(), buffer->getIndexes().size());
        c->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");

        if (i == 0) {
            c->loadTexture("./parallax4.png");
        }
        if (i == 1) {
            c->loadTexture("./sun.png");
        }
        if (i == 2) {
            c->loadTexture("./texture3.png");
        }
        c->_tf->_x = i * 1.5;
        c->_tf->_y = i * 1.5;
        c->_tf->_z = 0;
        this->add(c);
    }
}


void Scene::setup() {
    setup_visitor();

    VisitStart start;
    for (std::map<unsigned, Component*>::const_iterator it = _components.begin(); it != _components.end(); ++it) {
        it->second->accept(start);
    }
}

void Scene::init() {
    // Initialize GLFW. Most GLFW functions will not work before doing this.
    if (!glfwInit()) {
        throw;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    // Create the window
    _window = glfwCreateWindow(800, 600, "Graphic Engine", nullptr, nullptr);
    if (_window == nullptr) {
        std::cerr << "Failed to create the GLFW window" << std::endl;
        throw;
    }

    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(_window, keyCallback);

    // Make the OpenGL context current.
    glfwMakeContextCurrent(_window);

    // Enable v-sync.
    glfwSwapInterval(1);

    // Make the window visible.
    glfwShowWindow(_window);
    gladLoadGL();
}


void Scene::demo() {
    VisitAwakeStart awakeStart;
    VisitUpdate update;

    for (std::map<unsigned, Component*>::const_iterator it = _components.begin(); it != _components.end(); ++it) {
        it->second->accept(awakeStart);
        it->second->accept(update);
    }
}

void Scene::render() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        demo();
        // Poll for window events. The key callback above will only be
        // invoked during this call.
        glfwPollEvents();
        glfwSwapBuffers(_window); // swap the color buffers.

    } while (!glfwWindowShouldClose(_window));
}
