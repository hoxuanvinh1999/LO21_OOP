#ifndef REFERENCEITERATOR_H
#define REFERENCEITERATOR_H

#include <type_traits>

/**
 * @class ReferenceIterator
 * @brief Itérateur sur les références des éléments pointés d'un autre itérateur.
 */
template<typename Iter>
class reference_iterator {
public:
    /**
     * @typedef value_type
     * @brief Type des éléments de l'itérateur.
     */
    using value_type = typename std::remove_pointer<typename Iter::value_type>::type;
    /**
     * @typedef pointer
     * @brief Type des pointeurs d'éléments de l'itérateur.
     */
    using pointer = value_type*;
    /**
     * @typedef reference
     * @brief Type de la référence de l'élément renvoyé par l'itérateur.
     */
    using reference = value_type&;
    /**
     * @brief Constructeur vide d'un reference_iterator.
     */
    reference_iterator() = default;
    /**
     * @brief Constructeur par copie d'un reference_iterator.
     * @param it ReferenceIterator à copier.
     */
    reference_iterator(const reference_iterator& it) = default;
    /**
     * @brief Opérateur d'affectation d'un reference_iterator.
     * @param it reference_iterator à affecter à l'instance.
     * @return Une référence sur l'instance après affectation.
     */
    reference_iterator& operator=(const reference_iterator& it) = default;
    /**
     * @brief Constructeur par copie de l'itérateur à transformer.
     * @param it Itérateur à transformer.
     */
    reference_iterator(const Iter& it): current(it) {}
    /**
     * @brief Opérateur de pré-incrémentation.
     * @return Une référence sur l'itérateur incrémenté.
     */
    reference_iterator& operator++() { ++current; return *this; }
    /**
     * @brief Opérateur de post-incrémentation.
     * @return Une copie de l'itérateur avant incrémentation.
     */
    reference_iterator operator++(int) { reference_iterator old = *this;  ++current; return old; }
    /**
     * @brief Opérateur de pré-décrémentation.
     * @return Une référence sur l'itérateur décrémenté.
     */
    reference_iterator& operator--() { --current; return *this; }
    /**
     * @brief Opération de post-décrémentation.
     * @return Une copie de l'itérateur avant décrémentation.
     */
    reference_iterator operator--(int) { reference_iterator old = *this;  --current; return old; }
    /**
     * @brief Opérateur d'addition par une valeur.
     * @param i Incrément à ajouter à l'itérateur.
     * @return Une copie de l'itérateur avec l'incrément.
     */
    reference_iterator operator+(int i) const { return reverse_iterator(current + i); }
    /**
     * @brief Opérateur de soustraction par une valeur.
     * @param i Décrément à soustraire à l'itérateur.
     * @return Une copie de l'itérateur avec le décrément.
     */
    reference_iterator operator-(int i) const { return reverse_iterator(current - i); }
    /**
     * @brief Opérateur d'incrémentation par une valeur.
     * @param i Incrément à ajouter à l'itérateur.
     * @return Une référence de l'itérateur après incrémentation.
     */
    reference_iterator& operator+=(int i) { current += i; return *this; }
    /**
     * @brief Opérateur de décrémentation par une valeur.
     * @param i Décrément à soustraire à l'itérateur.
     * @return Une référence de l'itérateur après décrémentation.
     */
    reference_iterator& operator-=(int i) { current -= i; return *this; }
    /**
     * @brief Opérateur d'égalité.
     * @param it Itérateur pour la comparaison.
     * @return Vrai si les deux itérateurs sont égaux, faux sinon.
     */
    bool operator==(const reference_iterator& it) { return current == it.current; }
    /**
     * @brief Opérateur de différence.
     * @param it Itérateur pour la comparaison.
     * @return Vrai si les deux itérateurs sont différents, faux sinon.
     */
    bool operator!=(const reference_iterator& it) { return current != it.current; }
    /**
     * @brief Opérateur inférieur ou égal.
     * @param it Opérateur pour la comparaison.
     * @return Vrai si l'itérateur est plus inférieur ou égale, faux sinon.
     */
    bool operator<=(const reference_iterator& it) const { return current <= it.current; }
    /**
     * @brief Opérateur supérieur ou égal
     * @param it Opérateur pour la comparaison.
     * @return Vrai si l'itérateur est supérieur ou égale, faux sinon.
     */
    bool operator>=(const reference_iterator& it) const { return current >= it.current; }
    /**
     * @brief Opérateur strictement inférieur.
     * @param it Opérateur pour la comparaison.
     * @return Vrai si l'itérateur strictement inférieur, faux sinon.
     */
    bool operator<(const reference_iterator& it) const { return current < it.current; }
    /**
     * @brief Opérateur strictement supérieur.
     * @param it Opérateur pour la comparaison.
     * @return Vrai si l'itérateur strictement supérieur, faux sinon.
     */
    bool operator>(const reference_iterator& it) const { return current > it.current; }
    /**
     * @brief Opérateur de récupération de l'élément courant de l'itérateur.
     * @return L'élément courant de l'itérateur.
     */
    reference operator*() const { return *(*current); }
private:
    /**
     * @brief Élement courant de l'itérateur de référence.
     */
    Iter current;
};

#endif // REFERENCEITERATOR_H
