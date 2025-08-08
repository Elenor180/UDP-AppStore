#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QList>
#include "Transactions.h"

class Customer {
private:
    QString name;
    QList<Transaction*> transactions;

public:
    explicit Customer(const QString& name);
    QString getName() const;
    ~Customer();  // destructor

    void addTransaction(Transaction* t);
    const QList<Transaction*>& getTransactions() const;

};

#endif // CUSTOMER_H
