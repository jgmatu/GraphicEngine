#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include "Scene.hpp"

int
main() {
    bool success = false;
    Scene *scene = new Scene();
    try {
        scene->init();
        scene->setup();
        scene->render();
        success = true;
    } catch (std::exception& e) {
          std::cout << e.what() << std::endl;
    }
    glfwTerminate();
    return (success) ? 0 : 1;
}
