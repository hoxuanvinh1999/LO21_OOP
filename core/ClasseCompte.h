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


#endif // CLASSECOMPTE_H
