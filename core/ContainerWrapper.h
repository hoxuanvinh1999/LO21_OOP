#ifndef CONTAINERWRAPPER_H
#define CONTAINERWRAPPER_H

/**
 * @brief The IteratorProxy class
 */

template<typename Container, typename Iter = typename Container::iterator>
class ContainerWrapper {
private:
    Container container;
public:
    using iterator = Iter;
    ContainerWrapper() = delete;
    ContainerWrapper(const Container& container): container(container) {}
    iterator begin() { return container.begin(); }
    iterator end() { return container.end(); }
    int size() const { return container.size(); }
};

#endif // CONTAINERWRAPPER_H
