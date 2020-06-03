#ifndef CONSTREFERENCEITERATOR_H
#define CONSTREFERENCEITERATOR_H

template<template <typename> class Container, typename T>
class ConstReferenceIterator : public Container<T*>::const_iterator {
public:
    typedef typename Container<T*>::iterator iterator;
    typedef typename Container<T*>::const_iterator const_iterator;
    ConstReferenceIterator(): Container<T*>::const_iterator() {}
    ConstReferenceIterator(const iterator& i): Container<T*>::const_iterator(i) {}
    ConstReferenceIterator(const const_iterator& i): Container<T*>::const_iterator(i) {}
    ConstReferenceIterator(const const_iterator&& i): Container<T*>::const_iterator(i) {}
    const T& operator*() { return *const_iterator::operator*(); }
};

#endif // CONSTREFERENCEITERATOR_H
