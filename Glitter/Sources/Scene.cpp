#include "Scene.hpp"
#include "BOX.h"

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
    cubes[0]->shader("./Glitter/GLSL/cube/vertex_1.glsl", "./Glitter/GLSL/cube/fragment_1.glsl");
    cubes[1]->shader("./Glitter/GLSL/cube/vertex_2.glsl", "./Glitter/GLSL/cube/fragment_2.glsl");
    cubes[2]->shader("./Glitter/GLSL/cube/vertex_3.glsl", "./Glitter/GLSL/cube/fragment_3.glsl");

    for (unsigned i = 0; i < NUM_CUBES; ++i) {
        cubes[i]->createUniform("projection");
        cubes[i]->createUniform("view");
        cubes[i]->createUniform("model");
        cubes[i]->createUniform("diffuseTexture");
    }

    cubes[0]->loadTexture("./textura.png");
    cubes[1]->loadTexture("./sun.png");
    cubes[2]->loadTexture("./moon.png");

    for (unsigned i = 0; i < NUM_CUBES; ++i) {
        this->add(cubes[i]);
    }
}

void Scene::setup() {
    setup_cubes();
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
    std::vector<Component*> cubes = std::vector<Component*>(NUM_CUBES);

    for (unsigned i = 0; i < NUM_CUBES; ++i) {
        cubes[i] = _components[i];
    }
    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {
            unsigned cube = abs(i + j) % NUM_CUBES;
            cubes[cube]->translate(glm::vec3(i * 3.5 , j * 3.5, 0.0));
            cubes[cube]->rotate(angle, glm::vec3(1.0f, -1.0f, 0.0f));

            cubes[cube]->setUniform("projection", _camera->_projection);
            cubes[cube]->setUniform("view", _camera->_view);
            cubes[cube]->setUniform("model", cubes[cube]->_model);
            cubes[cube]->setUniform("diffuseTexture", 0); // El índice es el mismo que en glActiveTexture()

            // Render...
            cubes[cube]->bind();
            cubes[cube]->texture();
            cubes[cube]->draw();
            cubes[cube]->identity();
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
