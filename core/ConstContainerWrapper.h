#ifndef CONSTCONTAINERWRAPPER_H
#define CONSTCONTAINERWRAPPER_H

#include "ConstReferenceIterator.h"

template<typename Container, typename ConstIter = typename Container::const_iterator>
class ConstContainerWrapper {
private:
    const Container container;
public:
    using iterator = ConstIter;
    ConstContainerWrapper() = delete;
    ConstContainerWrapper(const Container& container): container(container) {}
    iterator begin() const { return container.cbegin(); }
    iterator end() const { return container.cend(); }
    int size() const { return container.size(); }
};

#endif // CONSTCONTAINERWRAPPER_H
