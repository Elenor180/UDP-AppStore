#include "TransactionViewWidget.h"
#include <QVBoxLayout>
#include <QDateTime>
#include "StoreData.h"
#include "Customer.h"
#include "Transactions.h"
#include "Items.h"

TransactionViewWidget::TransactionViewWidget(QWidget* parent)
    : QWidget(parent) {

    QVBoxLayout* layout = new QVBoxLayout(this);

    treeView = new QTreeView(this);
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Customer Transactions"});

    treeView->setModel(model);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeView->setHeaderHidden(false);

    layout->addWidget(treeView);
    updateModel();  // initial load
}


QStandardItem* TransactionViewWidget::createCustomerNode(const QString& name) {
    auto* item = new QStandardItem("👤 " + name);
    item->setEditable(false);
    return item;
}

void TransactionViewWidget::updateModel() {
    model->clear();
    model->setHorizontalHeaderLabels({"Customer Transactions"});

    auto& customers = StoreData::instance().getCustomers();
    for (Customer* c : customers) {
        QStandardItem* customerItem = createCustomerNode(c->getName());

        for (Transaction* t : c->getTransactions()) {
            QString dateTimeStr = t->getDate().toString("yyyy-MM-dd hh:mm:ss");
            QStandardItem* transactionItem = createTransactionNode(dateTimeStr);

            for (const PurchasedItem& pItem : t->getItems()) {
                Item* item = pItem.item;
                int quantity = pItem.quantity;
                QString itemStr = item->getType() + ": \"" + item->getName() + "\" × " + QString::number(quantity);
                transactionItem->appendRow(new QStandardItem(itemStr));
            }

            customerItem->appendRow(transactionItem);
        }

        model->appendRow(customerItem);
    }

    treeView->expandAll();  //auto expand everything
}


QStandardItem* TransactionViewWidget::createTransactionNode(const QString& datetime) {
    auto* item = new QStandardItem("🧾 Transaction (" + datetime + ")");
    item->setEditable(false);
    return item;
}
