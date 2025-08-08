#include "Magazine.h"

Magazine::Magazine(const QString& name) : Item(name) {}
QString Magazine::getType() const {

    return "Magazine";

}
