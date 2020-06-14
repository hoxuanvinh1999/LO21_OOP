#ifndef CONTAINERWRAPPER_H
#define CONTAINERWRAPPER_H

/**
 * @class ContainerWrapper
 * @brief Classe représentant un wrapper d'une classe container avec un iterator spécifique
 */
template<typename Container, typename Iter = typename Container::iterator>
class ContainerWrapper {
private:
    /**
     * @brief Container wrappé par le wrapper.
     */
    Container container;
public:
    /**
     * @typedef iterator
     * @brief Itérateur sur les éléments du container.
     */
    using iterator = Iter;
    ContainerWrapper() = delete;
    /**
     * @brief Contructeur d'un ContainerWrapper
     * @param Container à wrapper.
     */
    ContainerWrapper(const Container& container): container(container) {}
    /**
     * @brief Récupère l'itérateur du début du parcours des éléments du container.
     * @return L'itérateur du début du parcours des éléments du container.
     */
    iterator begin() { return container.begin(); }
    /**
     * @brief Récupère l'itérateur de fin du parcours des éléments du container.
     * @return L'itérateur de fin du parcours des éléments du container.
     */
    iterator end() { return container.end(); }
    /**
     * @brief Recupère la taille du container.
     * @return La taille du container.
     */
    int size() const { return container.size(); }
};

#endif // CONTAINERWRAPPER_H
