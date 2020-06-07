#ifndef CONSTREFERENCEITERATORPROXY_H
#define CONSTREFERENCEITERATORPROXY_H

#include "ConstReferenceIterator.h"

template<template <typename> class Container, typename T>
class ConstReferenceIteratorProxy {
private:
    const Container<T*> container;
public:
    typedef ConstReferenceIterator<Container, T> iterator;
    ConstReferenceIteratorProxy(const Container<T*>& container): container(container) {}
    iterator begin() const { return container.begin(); }
    iterator end() const { return container.end(); }
    int size() const { return container.size(); }
};

#endif // CONSTREFERENCEITERATORPROXY_H
