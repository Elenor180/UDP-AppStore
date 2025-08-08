#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Items.h"
#include <QString>

class ItemFactory {
public:
    static Item* createItem(const QString& type, const QString& name);

};

#endif // ITEMFACTORY_H
