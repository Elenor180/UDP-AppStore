#ifndef PURCHASEDITEM_H
#define PURCHASEDITEM_H


#include "Items.h"

struct PurchasedItem {

    Item* item;
    int quantity;

    PurchasedItem(Item* i, int q) : item(i), quantity(q) {}

};

#endif // PURCHASEDITEM_H
