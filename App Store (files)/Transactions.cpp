#include "Transactions.h"

Transaction::Transaction() : date(QDateTime::currentDateTime()) {}

void Transaction::addItem(Item *item, int quantity){

    items.append(PurchasedItem(item, quantity));

}

QDateTime Transaction::getDate() const {

    return date;

}

QList<PurchasedItem> Transaction::getItems() const {

    return items;

}
