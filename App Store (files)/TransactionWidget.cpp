#include "TransactionWidget.h"
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

#include "StoreData.h"
#include "Customer.h"
#include "Transactions.h"

TransactionWidget::TransactionWidget(QWidget* parent)
    : QWidget(parent) {
    setupUI();
}

void TransactionWidget::setupUI() {
    auto* layout = new QVBoxLayout(this);

    // Customer selection
    layout->addWidget(new QLabel("Select Customer:"));
    customerCombo = new QComboBox(this);
    for (Customer* c : StoreData::instance().getCustomers())
        customerCombo->addItem(c->getName());
    layout->addWidget(customerCombo);

    // Item section label
    layout->addWidget(new QLabel("Items:"));

    // Item spinboxes and labels
    for (Item* item : StoreData::instance().getItems()) {
        QLabel* label = new QLabel(item->getName() + " (" + item->getType() + ")", this);
        QSpinBox* spin = new QSpinBox(this);
        spin->setRange(0, 100);

        layout->addWidget(label);
        layout->addWidget(spin);

        itemInputs[item->getName()] = spin;
    }

    // Record transaction button
    recordButton = new QPushButton("Record Transaction", this);
    layout->addWidget(recordButton);
    connect(recordButton, &QPushButton::clicked, this, &TransactionWidget::recordTransaction);
}

void TransactionWidget::recordTransaction() {
    if (customerCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "Error", "Select a customer.");
        return;
    }

    const QString customerName = customerCombo->currentText();
    Customer* customer = nullptr;
    for (Customer* c : StoreData::instance().getCustomers()) {
        if (c->getName() == customerName) {
            customer = c;
            break;
        }
    }

    if (!customer) {
        QMessageBox::warning(this, "Error", "Selected customer not found.");
        return;
    }

    auto* t = new Transaction();

    for (Item* item : StoreData::instance().getItems()) {
        QSpinBox* spin = itemInputs.value(item->getName(), nullptr);
        if (!spin) {
            qWarning() << "Missing spinbox for item:" << item->getName();
            continue;
        }
        int qty = spin->value();
        if (qty > 0)
            t->addItem(item, qty);
    }

    if (t->getItems().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select at least one item.");
        delete t;
        return;
    }

    customer->addTransaction(t);
    QMessageBox::information(this, "Success", "Transaction recorded.");
    emit transactionRecorded();

    // Reset spinboxes to 0
    for (auto it = itemInputs.constBegin(); it != itemInputs.constEnd(); ++it)
        it.value()->setValue(0);
}

void TransactionWidget::refreshCustomerList() {
    customerCombo->clear();
    for (Customer* c : StoreData::instance().getCustomers()) {
        customerCombo->addItem(c->getName());
    }
}

// SAFE refresh of the items UI to avoid crashes
void TransactionWidget::refreshItems() {
    // Clear old spinboxes and labels related to items
    for (auto spin : itemInputs) {
        if (spin) {
            spin->deleteLater();
        }
    }
    itemInputs.clear();

    auto layout = qobject_cast<QVBoxLayout*>(this->layout());
    if (!layout)
        return;

    // Remove all widgets after customerCombo which is at index 1
    // Layout structure:


    // Remove widgets starting from index 2 until before the recordButton which is last
    while (layout->count() > 3) {
        QLayoutItem* item = layout->takeAt(2);  // always remove at index 2
        if (item) {
            QWidget* w = item->widget();
            if (w) {
                w->deleteLater();
            }
            delete item;
        }
    }

    // Re add "Items:" label
    layout->insertWidget(2, new QLabel("Items:", this));

    int insertPos = 3; // after "Items:" label
    for (Item* item : StoreData::instance().getItems()) {
        QLabel* label = new QLabel(item->getName() + " (" + item->getType() + ")", this);
        QSpinBox* spin = new QSpinBox(this);
        spin->setRange(0, 100);

        layout->insertWidget(insertPos++, label);
        layout->insertWidget(insertPos++, spin);
        itemInputs[item->getName()] = spin;
    }
}
