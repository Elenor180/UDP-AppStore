#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDateTime>
#include <QList>
#include "PurchasedItem.h"

class Transaction {
private:
    QDateTime date;
    QList<PurchasedItem> items;


public:
    Transaction();

    void addItem(Item* item, int quantity);

    QDateTime getDate() const; // Gets current date of purchase
    QList<PurchasedItem> getItems() const;


};

#endif // TRANSACTIONS_H
