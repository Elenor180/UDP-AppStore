#ifndef BOOK_H
#define BOOK_H

#include "Items.h"


//Concrete class respesenting book item
class Book : public Item {
public:
    explicit Book(const QString& name); //Constructor
    QString getType() const override; //Return Book as type

};

#endif // BOOK_H
