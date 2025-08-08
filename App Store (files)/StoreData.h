#ifndef STOREDATA_H
#define STOREDATA_H

#include <QList>
#include "Items.h"
#include "Customer.h"

//Singleton class to manage store data

class StoreData {
private:
    QList<Item*> items; //Master item list

    StoreData(); // Private constructor for singleton pattern
    QList<Customer*> customers;


public:
    static StoreData& instance();   //Accessor to singleton instance
    void addItem(Item* item);
    const QList<Item*>& getItems() const; //get current item list
    void addCustomer(Customer* c);
    const QList<Customer*>& getCustomers() const;
    void replaceItems(const QList<Item*>& newItems);




    //Disable copy constructor and assignment
    StoreData(const StoreData&) = delete;
    StoreData& operator=(const StoreData&) = delete;

};

#endif // STOREDATA_H
