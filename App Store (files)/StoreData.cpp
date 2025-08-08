#include "StoreData.h"

StoreData::StoreData() {}

//Staic accessor for the singleton instance
StoreData& StoreData::instance(){
    static StoreData instance;
    return instance;
}

//Add a new item to the list
void StoreData::addItem(Item *item){
    items.append(item);
}

//Return the list of all items

const QList<Item*>& StoreData::getItems() const{
    return items;

}

//Add a new customer to the list
void StoreData::addCustomer(Customer *c){
    customers.append(c);

}

void StoreData::replaceItems(const QList<Item*>& newItems) {
    items = newItems;  // Replace the internal list
}


//Return the list of all customers
const QList<Customer*>& StoreData::getCustomers() const{

    return customers;
}
