#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include "Scene.hpp"
//#include "BTree.hpp"

//#include "_Component.hpp"
//#include "VisitorScene.hpp"

#include <iostream>
#include <string>

#include "Element.hpp"
#include "This.hpp"
#include "Component.hpp"

#include "Visitor.hpp"

/*
int main() {
    Element *list[] = { new This(), new  This(), new This() };

    VisitAwakeStart awake;
    for (unsigned i = 0; i < 1; i++) {
        list[i]->accept(awake);
    }

    VisitStart start;
    for (unsigned i = 0; i < 1; i++) {
        list[i]->accept(start);
    }

    VisitUpdate update;
    for (unsigned i = 0; i < 1; i++) {
        list[i]->accept(update);
    }
}
*/

int main() {
/*
    BTree *tree = new BTree();

    tree->insert(10);
    tree->insert(6);
    tree->insert(14);
    tree->insert(5);
    tree->insert(8);
    tree->insert(11);
    tree->insert(18);
    tree->insert(22);
    tree->insert(7);
    tree->insert(15);
    tree->insert(33);
    tree->insert(9);
    tree->insert(12);
    tree->insert(19);
    tree->inorder_print();

    delete tree;
*/

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
