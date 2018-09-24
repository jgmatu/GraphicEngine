#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

// System Headers.
#include <vector>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <exception>
#include <math.h>       /* sin */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Triangle.hpp"
#include "Cube.hpp"
#include "Camera.hpp"

GLFWwindow* window;

static void
keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
      std::cout << scancode << " " << mods << std::endl;

      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
      }
}

void
init()
{
    // Initialize GLFW. Most GLFW functions will not work before doing this.
    if (!glfwInit()) {
        throw;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    // Create the window
    window = glfwCreateWindow(800, 600, "Graphic Engine", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create the GLFW window" << std::endl;
        throw;
    }

    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(window, keyCallback);

    // Make the OpenGL context current.
    glfwMakeContextCurrent(window);

    // Enable v-sync.
    glfwSwapInterval(1);

    // Make the window visible.
    glfwShowWindow(window);
    gladLoadGL();
}

void
loop()
{
    Camera *camera = new Camera();

    Cube *cube = new Cube();

    cube->vertexArrayID();
    cube->genVertexBuffer();
    cube->shader();

    cube->createUniform("projection");
    cube->createUniform("view");
    cube->createUniform("model");

    cube->createUniform("diffuseTexture");
    cube->loadTexutre("./textura.png");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLint64 timer;
    do {
        glGetInteger64v(GL_TIMESTAMP, &timer);
        float angle = std::fmod((timer / 1000000000.0), (2.0f * M_PI));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = -2; i < 3; ++i) {

            for (int j = -2; j < 3; ++j) {
                cube->translate(glm::vec3(i * 3.5 , j * 3.5, 0.0));
                cube->rotate(angle, glm::vec3(1.0f, -1.0f, 0.0f));

                cube->setUniform("projection", camera->_projection);
                cube->setUniform("view", camera->_view);
                cube->setUniform("model", cube->_model);
                cube->setUniform("diffuseTexture", 0); // El índice es el mismo que en glActiveTexture()

                // Render...
                cube->bind();
                cube->texture();
                cube->draw();
                cube->identity();
            }
        }

        // Poll for window events. The key callback above will only be
        // invoked during this call.
        glfwPollEvents();
        glfwSwapBuffers(window); // swap the color buffers.

    } while (!glfwWindowShouldClose(window));
}

int
run()
{
      bool success = false;
      try {
            init();
            loop();
            success = true;
      } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
      }
      glfwTerminate();
      return (success) ? 0 : 1;
}

int
main() {
      return run();
}
