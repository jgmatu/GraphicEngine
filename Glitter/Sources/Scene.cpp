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

void Scene::setup_cubes() {
    const unsigned static NUM_CUBES = 3;
    std::vector<Component*> cubes = std::vector<Component*>(NUM_CUBES);

    for (int i = 0; i < 3; ++i) {
        cubes[i] = new Component();

        cubes[i]->setVertexPos(cubeVertexPos);
        cubes[i]->setVertexNormal(cubeVertexNormal);
        cubes[i]->setVertexTexCoord(cubeVertexTexCoord);
        cubes[i]->setTriangleIndex(cubeTriangleIndex, cubeNTriangleIndex);

        cubes[i]->vertexArrayID();
        cubes[i]->genVertexBufferPosition();
        cubes[i]->genVertexBufferNormal();
        cubes[i]->genVertexBufferTextCoord();
        cubes[i]->genVertexBufferIndex();
    }
    cubes[0]->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");
    cubes[1]->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");
    cubes[2]->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");

    for (unsigned i = 0; i < NUM_CUBES; ++i) {
        cubes[i]->createUniform("projection");
        cubes[i]->createUniform("view");
        cubes[i]->createUniform("model");
        cubes[i]->createUniform("diffuseTexture");
    }

    cubes[0]->loadTexture("./texture2.png");
    cubes[1]->loadTexture("./sun.png");
    cubes[2]->loadTexture("./parallax4.png");

    for (unsigned i = 0; i < NUM_CUBES; ++i) {
        this->add(cubes[i]);
    }
}

void Scene::setup_spheres() {
    static const unsigned NUM_SPHERES = 3;
    Sphere *buffer = new Sphere();
    buffer->createBuffer();

    std::vector<Component*> spheres = std::vector<Component*>(NUM_SPHERES);

    for (unsigned i = 0; i < NUM_SPHERES; ++i) {
        spheres[i] = new Component();

        spheres[i]->setVertexPos(buffer->getPosVertex());
        spheres[i]->setVertexNormal(buffer->getNormals());
        spheres[i]->setVertexTexCoord(buffer->getTexCoords());
        spheres[i]->setTriangleIndex(buffer->getIndexes(), buffer->getIndexes().size());

        spheres[i]->vertexArrayID();
        spheres[i]->genVertexBufferPosition();
        spheres[i]->genVertexBufferNormal();
        spheres[i]->genVertexBufferTextCoord();
        spheres[i]->genVertexBufferIndex();
    }
    spheres[0]->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");
    spheres[1]->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");
    spheres[2]->shader("./Glitter/GLSL/cube/vertex.glsl", "./Glitter/GLSL/cube/fragment.glsl");

    for (unsigned i = 0; i < NUM_SPHERES; ++i) {
        spheres[i]->createUniform("projection");
        spheres[i]->createUniform("view");
        spheres[i]->createUniform("model");
        spheres[i]->createUniform("diffuseTexture");
    }

    spheres[0]->loadTexture("./parallax4.png");
    spheres[1]->loadTexture("./sun.png");
    spheres[2]->loadTexture("./texture3.png");

    for (unsigned i = 0; i < NUM_SPHERES; ++i) {
        this->add(spheres[i]);
    }
}

void Scene::setup() {
//    setup_cubes();
    setup_spheres();
}

void Scene::add(Component *component) {
        _components.insert(std::pair<const unsigned int, Component*>(_ncomponent++, component));
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

void Scene::demo(float angle) {
    const static unsigned NUM_CUBES = 3;
    std::vector<Component*> components = std::vector<Component*>(NUM_CUBES);

    for (unsigned i = 0; i < NUM_CUBES; ++i) {
        components[i] = _components[i];
    }
    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {
            unsigned ncomponent = abs(i + j) % NUM_CUBES;
            components[ncomponent]->translate(glm::vec3(i * 3.5 , j * 3.5, 0.0));
            components[ncomponent]->rotate(angle, glm::vec3(1.0f, -1.0f, 0.0f));

            components[ncomponent]->setUniform("projection", _camera->_projection);
            components[ncomponent]->setUniform("view", _camera->_view);
            components[ncomponent]->setUniform("model", components[ncomponent]->_model);
            components[ncomponent]->setUniform("diffuseTexture", 0); // El índice es el mismo que en glActiveTexture()

            // Render...
            components[ncomponent]->bind();
            components[ncomponent]->texture();
            components[ncomponent]->draw();
            components[ncomponent]->identity();
        }
    }
}

void Scene::render() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLint64 timer;
    do {
        glGetInteger64v(GL_TIMESTAMP, &timer);
        float angle = std::fmod((timer / 1000000000.0), (2.0f * M_PI));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        demo(angle);

        // Poll for window events. The key callback above will only be
        // invoked during this call.
        glfwPollEvents();
        glfwSwapBuffers(_window); // swap the color buffers.

    } while (!glfwWindowShouldClose(_window));
}

/*
std::vector<Cube*> cubes = std::vector<Cube*>(NUM_CUBES);
for (int i = 0; i < 3; ++i) {
    cubes[i] = new Cube();
    cubes[i]->vertexArrayID();
    cubes[i]->genVertexBufferPosition();
    cubes[i]->genVertexBufferNormal();
    cubes[i]->genVertexBufferTextCoord();
    cubes[i]->genVertexBufferIndex();
}
cubes[0]->shader("./Glitter/GLSL/cube/vertex_1.glsl", "./Glitter/GLSL/cube/fragment_1.glsl");
cubes[1]->shader("./Glitter/GLSL/cube/vertex_2.glsl", "./Glitter/GLSL/cube/fragment_2.glsl");
cubes[2]->shader("./Glitter/GLSL/cube/vertex_3.glsl", "./Glitter/GLSL/cube/fragment_3.glsl");

for (unsigned i = 0; i < NUM_CUBES; ++i) {
    cubes[i]->createUniform("projection");
    cubes[i]->createUniform("view");
    cubes[i]->createUniform("model");
    cubes[i]->createUniform("diffuseTexture");
}

cubes[0]->loadTexutre("./textura.png");
cubes[1]->loadTexutre("./sun.png");
cubes[2]->loadTexutre("./moon.png");
*/
