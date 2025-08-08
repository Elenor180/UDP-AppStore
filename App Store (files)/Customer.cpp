#include "Customer.h"
#include <QtAlgorithms> // for qDeleteAll

Customer::Customer(const QString &name) : name(name) {}

QString Customer::getName() const {
    return name;
}

void Customer::addTransaction(Transaction *t) {
    transactions.append(t);
}

const QList<Transaction*>& Customer::getTransactions() const {
    return transactions;
}

Customer::~Customer() {
    // Delete all transactions owned by this customer to avoid memory leaks
    qDeleteAll(transactions);
    transactions.clear();
}
