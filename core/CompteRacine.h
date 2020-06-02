#ifndef COMPTERACINE_H
#define COMPTERACINE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "Compte.h"

class CompteRacine : public CompteAbstrait {
private:
    CompteRacine(): CompteAbstrait("Compte racine", AUCUN) {}
    friend class ComptabiliteManager;
public:
    TypeCompte getType() const override { return RACINE; }
};

#endif // COMPTERACINE_H
