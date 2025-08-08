#ifndef TRANSACTIONVIEWWIDGET_H
#define TRANSACTIONVIEWWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

class TransactionViewWidget : public QWidget {
    Q_OBJECT
public:
    explicit TransactionViewWidget(QWidget* parent = nullptr);

public slots:
    void updateModel();

private:
    QTreeView* treeView;
    QStandardItemModel* model;

    QStandardItem* createCustomerNode(const QString& name);
    QStandardItem* createTransactionNode(const QString& datetime);
};

#endif // TRANSACTIONVIEWWIDGET_H
