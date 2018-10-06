#ifndef THIS_H
#define THIS_H

#include <iostream>
#include <string>

#include "Element.hpp"

class This: public Element {

public:

    void accept(Visitor &v);

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart() {
        std::cout << "awakeStart" << '\n';
    };

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start() {
        std::cout << "start" << '\n';
    };

    // Metodo para empezar con el patrón de diseño.
    void update() {
        std::cout << "update" << '\n';
    };

};

#endif
