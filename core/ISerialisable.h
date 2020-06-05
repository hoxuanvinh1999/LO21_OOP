#ifndef ISERIALISABLE_H
#define ISERIALISABLE_H

#include <QDomElement>

class ISerialisable {
public:
    virtual QDomElement serialiser(QDomDocument& doc) const = 0;
    virtual ~ISerialisable() = default;
};

#endif // ISERIALISABLE_H
