#include "Items.h"

Item::Item(const QString &name) : name(name) {}
QString Item::getName() const {

    return name;

}
