#ifndef CONSTREFERENCEITERATOR_H
#define CONSTREFERENCEITERATOR_H

#include <type_traits>
#include "ReferenceIterator.h"

/**
 * @class ConstReferenceIterator
 * @brief Itérateur sur les références constantes des éléments pointés d'un container.
 */
template<typename Container>
class ConstReferenceIterator : public Container::const_iterator {
private:
    /**
     * @typedef iterator
     * @brief Itérateur par défaut sur les éléments du container.
     */
    using iterator = typename Container::iterator;
    /**
     * @typedef const_iterator
     * @brief Itérateur par défaut sur les éléments constants du container.
     */
    using const_iterator = typename Container::const_iterator;
public:
    /**
     * @typedef value_type
     * @brief Type des éléments de l'itérateur.
     */
    using value_type = typename const_iterator::value_type;
    /**
     * @typedef pointer
     * @brief Type des pointeurs d'éléments de l'itérateur.
     */
    using pointer = typename const_iterator::pointer;
    /**
     * @typedef reference
     * @brief Type de la référence de l'élément renvoyé par l'itérateur.
     */
    using reference = const typename std::remove_pointer<value_type>::type&;
    /**
     * @brief Constructeur vide d'un ConstReferenceIterator.
     */
    ConstReferenceIterator(): const_iterator() {}
    /**
     * @brief Constructeur par copie d'un ConstReferenceIterator.
     * @param i ConstReferenceIterator à copier
     */
    ConstReferenceIterator(const ConstReferenceIterator& i): const_iterator(i) {}
    /**
     * @brief Constructeur par copie d'un ReferenceIterator.
     * @param i ReferenceIterator à copier
     */
    ConstReferenceIterator(const ReferenceIterator<Container>& i): const_iterator(i) {}
    /**
     * @brief Constructeur par copie d'un itérateur par défaut du container.
     * @param i Itérateur par défaut à recopier.
     */
    ConstReferenceIterator(const iterator& i): const_iterator(i) {}
    /**
     * @brief Constructeur par copie d'un const itérateur par défaut du container.
     * @param i Const itérateur par défaut à recopier.
     */
    ConstReferenceIterator(const const_iterator& i): const_iterator(i) {}
    /**
     * @brief Opérateur d'affectation d'un ConstReferenceIterator.
     * @param i ConstReferenceIterator à affecter à l'instance.
     * @return Un référence sur l'instance après affectation.
     */
    ConstReferenceIterator& operator=(const ConstReferenceIterator& i) { const_iterator::operator=(i); return *this; }
    /**
     * @brief Opérateur d'affectation d'un ReferenceIterator.
     * @param i ReferenceIterator à affecter à l'instance.
     * @return Un référence sur l'instance après affectation.
     */
    ConstReferenceIterator& operator=(const ReferenceIterator<Container>& i) { const_iterator::operator=(i); return *this; }
    /**
     * @brief Opérateur de récupération de la référence de l'élément courant de l'itérateur.
     * @return La référence de l'élément courant de l'itérateur.
     */
    reference operator*() { return *const_iterator::operator*(); }
};

#endif // CONSTREFERENCEITERATOR_H
