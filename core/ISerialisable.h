#ifndef ISERIALISABLE_H
#define ISERIALISABLE_H

#include <QDomElement>

/**
 * @class ISerialisable
 * @brief Classe représentant un objet sérialisable en élément XML.
 */
class ISerialisable {
public:
    /**
     * @brief Sérialise l'objet sous forme d'un élément XML.
     * @param doc Document XML dans lequel doit se trouver l'objet sérialisé.
     * @return L'objet sous forme d'un élément XML.
     */
    virtual QDomElement serialiser(QDomDocument& doc) const = 0;
    /**
      * @brief Destructeur de l'objet sérialisable.
      */
    virtual ~ISerialisable() = default;
};

#endif // ISERIALISABLE_H
