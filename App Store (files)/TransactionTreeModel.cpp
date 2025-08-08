#include "TransactionTreeModel.h"
#include "StoreData.h"
#include "Customer.h"
#include "Transactions.h"



TransactionTreeModel::TransactionTreeModel(QObject* parent)
    : QStandardItemModel(parent) {
    setHorizontalHeaderLabels({"Transactions"});
    refreshModel();
}

void TransactionTreeModel::refreshModel() {
    clear();
    setHorizontalHeaderLabels({"Transactions"});

    for (Customer* customer : StoreData::instance().getCustomers()) {
        auto* customerItem = new QStandardItem("📦 " + customer->getName());

        for (Transaction* transaction : customer->getTransactions()) {
            QString tLabel = "📄 Transaction (" + transaction->getDate().toString("yyyy-MM-dd hh:mm:ss") + ")";
            auto* transactionItem = new QStandardItem(tLabel);

            for (const PurchasedItem& pi : transaction->getItems()) {
                QString itemText = QString("➤ %1: \"%2\" × %3")
                                       .arg(pi.item->getType(), pi.item->getName(), QString::number(pi.quantity));
                transactionItem->appendRow(new QStandardItem(itemText));
            }

            customerItem->appendRow(transactionItem);
        }

        appendRow(customerItem);
    }
}
