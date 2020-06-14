#ifndef TYPECOMPTE_H
#define TYPECOMPTE_H

#include <QString>

/**
 * @brief Nombre de types de comptes existants.
 */
static const uint NombreTypesComptes = 3;

/**
  * @brief Tableau des noms des types de comptes existants.
  */
static const QString NomsTypeCompte[NombreTypesComptes] = { "Racine", "Virtuel", "Simple" };

/**
 * @enum TypeCompte
 * @brief Enumération des différentes types de compte.
 */
enum TypeCompte {
    RACINE = 0,
    VIRTUEL,
    SIMPLE
};


/**
 * @brief Récupère le type de compte associé au nom fourni.
 * @param nom Nom du type de compte à récupérer.
 * @return Le type de compte associé au nom.
 */
TypeCompte getTypeCompte(const QString& nom);

/**
 * @class TypeCompteException
 * @brief Classe d'exception liée au type d'un compte.
 */
class TypeCompteException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée au type d'un compte.
     * @param message Message de l'exception.
     */
    TypeCompteException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~TypeCompteException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};


#endif // TYPECOMPTE_H
