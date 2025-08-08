#ifndef ITEMS_H
#define ITEMS_H

#include <QString>

//Abstract base class for storing items

class Item {
protected:
    QString name; //Name of the item stored here

public:
    explicit Item(const QString& name); //Constructor
    virtual ~Item() = default; //Virtual destructor


    QString getName() const;  //Get Item name
    virtual QString getType() const = 0; // Pure virtual fuction to get item

};

#endif // ITEMS_H
