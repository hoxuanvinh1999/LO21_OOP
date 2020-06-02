#ifndef CLASSECOMPTE_H
#define CLASSECOMPTE_H

#include <QString>

static const QString NomsClasseCompte[] = { "", "Actif", "Passif", "Dépense", "Recette" };

enum ClasseCompte {
    AUCUN = 0,
    ACTIF,
    PASSIF,
    DEPENSE,
    RECETTE
};

#endif // CLASSECOMPTE_H
