#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Items.h"

//Concrete class represemting a magazine item
class Magazine : public Item {
public:
    explicit Magazine(const QString& name);
    QString getType() const override;

};

#endif // MAGAZINE_H
