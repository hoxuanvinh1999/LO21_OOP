#ifndef REFERENCEITERATOR_H
#define REFERENCEITERATOR_H

template<template <typename> class Container, typename T>
class ReferenceIterator : public Container<T*>::iterator {
public:
    typedef typename Container<T*>::iterator iterator;
    ReferenceIterator(): Container<T*>::iterator() {}
    ReferenceIterator(const iterator& i): Container<T*>::iterator(i) {}
    ReferenceIterator(const iterator&& i): Container<T*>::iterator(i) {}
    T& operator*() { return *iterator::operator*(); }
};

#endif // REFERENCEITERATOR_H
