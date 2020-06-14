#ifndef REFERENCEITERATOR_H
#define REFERENCEITERATOR_H

#include <type_traits>

/**
 * @brief Permet de parcourir (en lecture et en écriture) l'ensemble des comptes et transaction
 */

template<typename Container>
class ReferenceIterator : public Container::iterator {
private:
    using iterator =  typename Container::iterator;
public:
    using value_type = typename Container::value_type;
    using pointer = typename Container::pointer;
    using reference = typename std::remove_pointer<value_type>::type&;
    ReferenceIterator(): iterator() {}
    ReferenceIterator(const ReferenceIterator& i): iterator(i) {}
    ReferenceIterator(const iterator& i): iterator(i) {}
    ReferenceIterator(const iterator&& i): iterator(i) {}
    ReferenceIterator& operator=(const ReferenceIterator& i) { iterator::operator=(i); return *this; }
    reference operator*() { return *iterator::operator*(); }
};

#endif // REFERENCEITERATOR_H
