#ifndef COMPTEVIRTUEL_H
#define COMPTEVIRTUEL_H

#include "CompteAbstrait.h"
#include "CompteException.h"

class CompteRacine;

/**
 * @brief Classe des comptes virtuels (i.e. qui n'ont pas de solde mais peuvent avoir des sous comptes ayant un solde)
 */

class CompteVirtuel : public CompteAbstrait {
public:
    CompteVirtuel(const QString& nom, CompteAbstrait* parent);
    CompteVirtuel(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine);
    TypeCompte getType() const override { return VIRTUEL; }
    double getSolde() const override;
    void debiter(double) override { throw CompteException("Un compte virtuel ne peut être débité !"); }
    void crediter(double) override { throw CompteException("Un compte virtuel ne peut être crédité !"); }
};

#endif // COMPTEVIRTUEL_H
