#include "ItemFactory.h"
#include "Book.h"
#include "Magazine.h"

//Factory Method: creates book or Magazine based on tring type
Item* ItemFactory::createItem(const QString &type, const QString &name){

    if(type == "Book"){

        return new Book(name);

    }

    else if (type == "Magazine"){

        return new Magazine(name);
    }
    return nullptr;
}

