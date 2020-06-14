#ifndef CONSTCONTAINERWRAPPER_H
#define CONSTCONTAINERWRAPPER_H

/**
 * @class ConstContainerWrapper
 * @brief Classe représentant un wrapper d'une classe container constante avec un iterator spécifique
 */
template<typename Container, typename ConstIter = typename Container::const_iterator>
class ConstContainerWrapper {
private:
    /**
     * @brief Container constant wrappé par le wrapper.
     */
    const Container container;
public:
    /**
     * @typedef iterator
     * @brief Itérateur sur les éléments constants du container.
     */
    using iterator = ConstIter;
    ConstContainerWrapper() = delete;
    /**
     * @brief Contructeur d'un ConstContainerWrapper
     * @param container Container à wrapper.
     */
    ConstContainerWrapper(const Container& container): container(container) {}
    /**
     * @brief Récupère l'itérateur du début du parcours des éléments constants du container.
     * @return L'itérateur du début du parcours des éléments constants du container.
     */
    iterator begin() const { return container.cbegin(); }
    /**
     * @brief Récupère l'itérateur de fin du parcours des éléments constants du container.
     * @return L'itérateur de fin du parcours des éléments constants du container.
     */
    iterator end() const { return container.cend(); }
    /**
     * @brief Recupère la taille du container.
     * @return La taille du container.
     */
    int size() const { return container.size(); }
};

#endif // CONSTCONTAINERWRAPPER_H
