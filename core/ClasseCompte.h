#ifndef CLASSECOMPTE_H
#define CLASSECOMPTE_H

#include <QString>

/**
 * @brief Nombre de classes de comptes existantes.
 */
static const uint NombreClassesComptes = 5;

/**
  * @brief Tableau des noms des classes de comptes existantes.
  */
static const QString NomsClasseCompte[NombreClassesComptes] = { QString(), "Actif", "Passif", "Dépense", "Recette" };

/**
 * @enum ClasseCompte
 * @brief Enumération des différentes classes de compte.
 */
enum ClasseCompte {
    AUCUN = 0,
    ACTIF,
    PASSIF,
    DEPENSE,
    RECETTE
};

/**
 * @brief Récupère la classe de compte associée au nom fourni.
 * @param nom Nom du type de classe compte à récupérer.
 * @return Le type de classe compte associé au nom.
 */
ClasseCompte getClasseCompte(const QString& nom);

/**
 * @class ClasseCompteException
 * @brief Classe d'exception liée à la classe d'un compte.
 */
class ClasseCompteException : public std::exception {
private:
    /**
     * @brief Message de l'exception.
     */
    QString message;
public:
    /**
     * @brief Constructeur d'une exception liée à la classe d'un compte.
     * @param message Message de l'exception.
     */
    ClasseCompteException(const QString& message) noexcept : message(message) {}
    /**
     * @brief Destructeur de l'exception.
     */
    virtual ~ClasseCompteException() noexcept {}
    /**
     * @brief Recupère le message propre à l'exception.
     * @return Le message propre à l'exception.
     */
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};


#endif // CLASSECOMPTE_H
