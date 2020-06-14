#ifndef COMPTERACINE_H
#define COMPTERACINE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "Compte.h"

/**
 * @class CompteRacine
 * @brief Classe représentant un compte racine dans une gestion de comptabilité.
 */
class CompteRacine : public CompteAbstrait {
public:
    /**
     * @brief Constructeur d'un compte racine.
     */
    CompteRacine(): CompteAbstrait("Compte racine", AUCUN) {}
    /**
     * @brief Débite le compte d'un montant donné.
     * @param montant Montant à débiter au compte.
     */
    void debiter(double) override { throw CompteException("Un compte racine ne peut être débité !"); }
    /**
     * @brief Crédite le compte d'un montant donné.
     * @param montant Montant à créditer au compte.
     */
    void crediter(double) override { throw CompteException("Un compte racine ne peut être crédité !"); }
    /**
     * @brief Récupère le solde du compte.
     * @return Le solde du compte.
     */
    double getSolde() const override;
    /**
     * @brief Récupère le type du compte.
     * @return Le type du compte.
     */
    TypeCompte getType() const override { return RACINE; }
};

#endif // COMPTERACINE_H
