#ifndef TRANSACTIONTREEMODEL_H
#define TRANSACTIONTREEMODEL_H

#include <QStandardItemModel>

class TransactionTreeModel : public QStandardItemModel {
    Q_OBJECT
public:
    explicit TransactionTreeModel(QObject* parent = nullptr);
    void refreshModel();
};

#endif // TRANSACTIONTREEMODEL_H
