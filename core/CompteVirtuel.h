#ifndef COMPTEVIRTUEL_H
#define COMPTEVIRTUEL_H

#include "CompteAbstrait.h"
#include "CompteException.h"

class CompteRacine;

class CompteVirtuel : public CompteAbstrait {
public:
    CompteVirtuel(const QString& nom, CompteAbstrait* parent);
    CompteVirtuel(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine);
    TypeCompte getType() const override { return VIRTUEL; }
    double getSolde() const override;
    double getSoldeRapprochement() const override;
    void debiter(double) override { throw CompteException("Un compte virtuel ne peut être débité !"); }
    void crediter(double) override { throw CompteException("Un compte virtuel ne peut être crédité !"); }
};

#endif // COMPTEVIRTUEL_H
