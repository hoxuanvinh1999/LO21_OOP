#ifndef COMPTEVIRTUEL_H
#define COMPTEVIRTUEL_H

#include "CompteAbstrait.h"

class CompteRacine;

class CompteVirtuel : public CompteAbstrait {
public:
    CompteVirtuel(const QString& nom, CompteAbstrait* parent);
    CompteVirtuel(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine);
    TypeCompte getType() const override { return VIRTUEL; }
};

#endif // COMPTEVIRTUEL_H
