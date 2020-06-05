#ifndef COMPTERACINE_H
#define COMPTERACINE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "Compte.h"

class CompteRacine : public CompteAbstrait {
public:
    CompteRacine(): CompteAbstrait("Compte racine", AUCUN) {}
    TypeCompte getType() const override { return RACINE; }
};

#endif // COMPTERACINE_H
