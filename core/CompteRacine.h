#ifndef COMPTERACINE_H
#define COMPTERACINE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "Compte.h"

class CompteRacine : public CompteAbstrait {
public:
    CompteRacine(): CompteAbstrait("Compte racine", AUCUN) {}
    TypeCompte getType() const override { return RACINE; }
    double getSolde() const override;
    void debiter(double) override { throw CompteException("Un compte racine ne peut être débité !"); }
    void crediter(double) override { throw CompteException("Un compte racine ne peut être crédité !"); }
};

#endif // COMPTERACINE_H
