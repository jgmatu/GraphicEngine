#ifndef VISITOR_H
#define VISITOR_H

#include "Component.hpp"
#include "This.hpp"

// 2. Create a "visitor" base class w/ a visit() method for every "element" type
class Visitor {

public:

    virtual void visit(Element *e) = 0;

};

// 3. Create a "visitor" derived class for each "operation" to do on "elements"
// Crear el componente...
class VisitStart: public Visitor {

public:

    void visit(Element *e) {
        e->start();
    };
};

// 3. Create a "visitor" derived class for each "operation" to do on "elements"
// Activar el componente...
class VisitAwakeStart: public Visitor {

public:

    void visit(Element *e) {
        e->awakeStart();
    };
};


// 3. Create a "visitor" derived class for each "operation" to do on "elements"
// Actualizar las transformadas del componente...
class VisitUpdate: public Visitor {

public:

    void visit(Element *e) {
        e->update();
    };
};

#endif
