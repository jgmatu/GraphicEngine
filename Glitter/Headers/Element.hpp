#ifndef ELEMENT_H
#define ELEMENT_H

class Element {

public:

    // Metodo para empezar con el patrón de diseño
    virtual void accept(class Visitor &v) = 0;

    // Método que se llama cada vez que el Componente se activa.
    virtual void awakeStart() = 0;

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    virtual void start() = 0;

    // Método que realiza transformaciones, cálculos de cosas.
    virtual void update() = 0;


};

#endif
