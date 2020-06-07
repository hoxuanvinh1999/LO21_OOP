#ifndef CLASSECOMPTE_H
#define CLASSECOMPTE_H

#include <QString>

static const uint NombreClassesComptes = 5;
static const QString NomsClasseCompte[NombreClassesComptes] = { QString(), "Actif", "Passif", "Dépense", "Recette" };

enum ClasseCompte {
    AUCUN = 0,
    ACTIF,
    PASSIF,
    DEPENSE,
    RECETTE
};

ClasseCompte getClasseCompte(const QString& nom);

using namespace std;

class ClasseCompteException : public exception {
private:
    QString message;
public:
    ClasseCompteException(const QString& message) noexcept : message(message) {}
    virtual ~ClasseCompteException() noexcept {}
    const char* what() const noexcept override  { return message.toStdString().c_str(); }
};


#endif // CLASSECOMPTE_H
