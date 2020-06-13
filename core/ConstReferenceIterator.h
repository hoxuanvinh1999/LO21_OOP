#ifndef CONSTREFERENCEITERATOR_H
#define CONSTREFERENCEITERATOR_H

#include <type_traits>
#include "ReferenceIterator.h"

template<typename Container>

/**
 * @brief Permet de parcourir (en lecture seule) l'ensemble des comptes et transaction
 */

class ConstReferenceIterator : public Container::const_iterator {
private:
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
public:
    using value_type = typename const_iterator::value_type;
    using pointer = typename const_iterator::pointer;
    using reference = const typename std::remove_pointer<value_type>::type&;
    ConstReferenceIterator(): const_iterator() {}
    ConstReferenceIterator(const ConstReferenceIterator& i): const_iterator(i) {}
    ConstReferenceIterator(const ReferenceIterator<Container>& i): const_iterator(i) {}
    ConstReferenceIterator(const iterator& i): const_iterator(i) {}
    ConstReferenceIterator(const iterator&& i): const_iterator(i) {}
    ConstReferenceIterator(const const_iterator& i): const_iterator(i) {}
    ConstReferenceIterator(const const_iterator&& i): const_iterator(i) {}
    ConstReferenceIterator& operator=(const ConstReferenceIterator& i) { const_iterator::operator=(i); return *this; }
    ConstReferenceIterator& operator=(const ReferenceIterator<Container>& i) { const_iterator::operator=(i); return *this; }
    reference operator*() { return *const_iterator::operator*(); }
};

#endif // CONSTREFERENCEITERATOR_H
