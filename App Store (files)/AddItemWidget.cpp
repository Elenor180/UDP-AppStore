#include "AddItemWidget.h"
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "ItemFactory.h"
#include "StoreData.h"
#include "BackupManager.h"

BackupManager backupManager;

AddItemWidget::AddItemWidget(QWidget *parent) :QWidget(parent){

    setupUI();
}


//UI setup

void AddItemWidget::setupUI(){
    auto* layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter item name");

    bookRadio = new QRadioButton("Book", this);
    magazineRadio = new QRadioButton("Magazine", this);
    bookRadio->setChecked(true);

    auto* typeLayout = new QHBoxLayout;
    typeLayout->addWidget(bookRadio);
    typeLayout->addWidget(magazineRadio);

    addButton = new QPushButton("Add Item", this);
    addButton->setEnabled(true);

    layout->addWidget(nameEdit);
    layout->addLayout(typeLayout);
    layout->addWidget(addButton);


    //Connect button signal to slot

    connect(addButton, &QPushButton::clicked,this,&AddItemWidget::handleAddItem);

}

//Handle the add button logi
void AddItemWidget::handleAddItem(){
    const QString name = nameEdit->text().trimmed();
    if(name.isEmpty()){
        QMessageBox::warning(this, "Input Error", "Item name cannot be empty");
        return;
    }

    QString type = bookRadio->isChecked() ? "Book" : "Magazine";
    Item* item = ItemFactory::createItem(type, name);

    if (item){
        StoreData::instance().addItem(item);


        //Backup current item list after addition
        backupManager.saveBackup(StoreData::instance().getItems());

        QMessageBox::information(this, "Success", type + "\"" + name + "\" added,");
        emit itemAdded(); //Notify the rest of the program

        //Clear input
        nameEdit->clear();
        bookRadio->setChecked(true);
        nameEdit->setFocus();
    }
}

