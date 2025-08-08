#include "CustomerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>

#include "StoreData.h"
#include "Customer.h"

CustomerWidget::CustomerWidget(QWidget* parent)
    : QWidget(parent) {

    auto* layout = new QVBoxLayout(this);

    // Input layout
    auto* inputLayout = new QHBoxLayout;
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter customer name");
    addButton = new QPushButton("Add Customer", this);
    inputLayout->addWidget(nameEdit);
    inputLayout->addWidget(addButton);

    customerList = new QListWidget(this);

    layout->addLayout(inputLayout);
    layout->addWidget(customerList);

    connect(addButton, &QPushButton::clicked, this, &CustomerWidget::handleAddCustomer);

    refreshCustomerList();
}

void CustomerWidget::handleAddCustomer() {
    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Customer name cannot be empty.");
        return;
    }

    auto& store = StoreData::instance();
    for (Customer* existing : store.getCustomers()) {
        if (existing->getName().compare(name, Qt::CaseInsensitive) == 0) {
            QMessageBox::information(this, "Duplicate", "Customer already exists.");
            return;
        }
    }

    store.addCustomer(new Customer(name));
    nameEdit->clear();
    nameEdit->setFocus();
    refreshCustomerList();
    emit customerAdded();
}

void CustomerWidget::refreshCustomerList() {
    customerList->clear();
    for (Customer* c : StoreData::instance().getCustomers()) {
        customerList->addItem(c->getName());
    }
}
