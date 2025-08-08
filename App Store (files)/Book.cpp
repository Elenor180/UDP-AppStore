#include "Book.h"

Book::Book(const QString &name) : Item(name) {}
QString Book::getType() const {

    return "Book";
}
