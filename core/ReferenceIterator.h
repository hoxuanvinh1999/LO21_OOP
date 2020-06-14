#ifndef REFERENCEITERATOR_H
#define REFERENCEITERATOR_H

#include <type_traits>

/**
 * @class ReferenceIterator
 * @brief Itérateur sur les références des éléments pointés d'un container.
 */
template<typename Container>
class ReferenceIterator : public Container::iterator {
private:
    /**
     * @typedef iterator
     * @brief Itérateur par défaut sur les éléments du container.
     */
    using iterator =  typename Container::iterator;
public:
    /**
     * @typedef value_type
     * @brief Type des éléments de l'itérateur.
     */
    using value_type = typename Container::value_type;
    /**
     * @typedef pointer
     * @brief Type des pointeurs d'éléments de l'itérateur.
     */
    using pointer = typename Container::pointer;
    /**
     * @typedef reference
     * @brief Type de la référence de l'élément renvoyé par l'itérateur.
     */
    using reference = typename std::remove_pointer<value_type>::type&;
    /**
     * @brief Constructeur vide d'un ReferenceIterator
     */
    ReferenceIterator(): iterator() {}
    /**
     * @brief Constructeur par copie d'un ReferenceIterator
     * @param i ReferenceIterator à copier
     */
    ReferenceIterator(const ReferenceIterator& i): iterator(i) {}
    /**
     * @brief Constructeur par copie d'un itérateur par défaut du container.
     * @param i Itérateur par défaut à recopier.
     */
    ReferenceIterator(const iterator& i): iterator(i) {}
    /**
     * @brief Opérateur d'affectation d'un ReferenceIterator
     * @param i ReferenceIterator à affecter à l'instance.
     * @return Un référence sur l'instance après affectation.
     */
    ReferenceIterator& operator=(const ReferenceIterator& i) { iterator::operator=(i); return *this; }
    /**
     * @brief Opérateur de récupération de la référence de l'élément courant de l'itérateur.
     * @return La référence de l'élément courant de l'itérateur.
     */
    reference operator*() { return *iterator::operator*(); }
};

#endif // REFERENCEITERATOR_H
