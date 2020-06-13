#ifndef TYPECOMPTE_H
#define TYPECOMPTE_H

#include <QString>

static const uint NombreTypesComptes = 3;
static const QString NomsTypeCompte[NombreTypesComptes] = { "Racine", "Virtuel", "Simple" };

enum TypeCompte {
    RACINE = 0,
    VIRTUEL,
    SIMPLE
};

TypeCompte getTypeCompte(const QString& nom);


using namespace std;

/**
 * @brief Gère les exceptions liées au type d'un compte
 */

class TypeCompteException : public exception {
private:
    QString message;
public:
    TypeCompteException(const QString& message) noexcept : message(message) {}
    virtual ~TypeCompteException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};


#endif // TYPECOMPTE_H
