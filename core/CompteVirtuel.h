#ifndef COMPTEVIRTUEL_H
#define COMPTEVIRTUEL_H

#include "CompteAbstrait.h"
#include "CompteException.h"

class CompteRacine;

/**
 * @class CompteVirtuel
 * @brief Classe représentant une compte virtuel possédant de possibles comptes enfants.
 */
class CompteVirtuel : public CompteAbstrait {
public:
    /**
     * @brief Constructeur d'un compte virtuel ayant un compte parent.
     * @param nom Nom du compte virtuel.
     * @param parent Parent du compte virtuel.
     */
    CompteVirtuel(const QString& nom, CompteAbstrait* parent);
    /**
     * @brief Constructeur d'un compte virtuel se trouvant en dessous d'un compte racine.
     * @param nom Nom du compte virtuel.
     * @param classe Classe du compte virtuel.
     * @param racine Compte racine sous laquelle se trouve le compte virtuel.
     */
    CompteVirtuel(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine);
    /**
     * @brief Débite le compte d'un montant donné.
     */
    void debiter(double) override { throw CompteException("Un compte virtuel ne peut être débité !"); }
    /**
     * @brief Crédite le compte d'un montant donné.
     */
    void crediter(double) override { throw CompteException("Un compte virtuel ne peut être crédité !"); }
    /**
     * @brief Récupère le solde du compte.
     * @return Le solde du compte.
     */
    double getSolde() const override;
    /**
     * @brief Récupère le type du compte.
     * @return Le type du compte.
     */
    TypeCompte getType() const override { return VIRTUEL; }
};

#endif // COMPTEVIRTUEL_H
