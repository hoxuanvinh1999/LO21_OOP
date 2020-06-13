#ifndef CONSTREFERENCEITERATORPROXY_H
#define CONSTREFERENCEITERATORPROXY_H

#include "ConstReferenceIterator.h"

template<typename Container>
class ConstReferenceIteratorProxy {
private:
    const Container container;
public:
    using iterator = ConstReferenceIterator<Container>;
    ConstReferenceIteratorProxy() = delete;
    ConstReferenceIteratorProxy(const Container& container): container(container) {}
    iterator begin() const { return container.begin(); }
    iterator end() const { return container.end(); }
    int size() const { return container.size(); }
};

#endif // CONSTREFERENCEITERATORPROXY_H
