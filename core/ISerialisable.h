#ifndef ISERIALISABLE_H
#define ISERIALISABLE_H

#include <QDomElement>

class ISerialisable {
public:
    virtual QDomElement serialiser(QDomDocument& owner) const = 0;
    virtual ~ISerialisable() = default;
};

#endif // ISERIALISABLE_H
