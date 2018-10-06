#include "Visitor.hpp"


void This::accept(Visitor &v) {
    v.visit(this);
}

void Component::accept(Visitor &v) {
    v.visit(this);
}
