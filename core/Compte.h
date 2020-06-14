#ifndef COMPTE_H
#define COMPTE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "CompteRacine.h"

/**
 * @class Compte
 * @brief Classe représentant un compte pouvant être affecté par des transactions.
 */
class Compte : public CompteAbstrait {
private:
    /**
     * @brief Solde du compte.
     */
    double solde;
public:
    /**
     * @brief Constructeur d'un compte ayant un compte parent.
     * @param nom Nom du compte.
     * @param parent Parent du compte.
     */
    Compte(const QString& nom, CompteAbstrait* parent);
    /**
     * @brief Constructeur d'un compte se trouvant en dessous d'un compte racine.
     * @param nom Nom du compte.
     * @param classe Classe du compte.
     * @param racine Compte racine sous laquelle se trouve le compte.
     */
    Compte(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine);
    /**
     * @brief Récupère le solde du compte.
     * @return Le solde du compte.
     */
    double getSolde() const override { return solde; }
    /**
     * @brief Retourne le type du compte.
     * @return Le type du compte.
     */
    TypeCompte getType() const override { return SIMPLE; }
    /**
     * @brief Sérialise le compte sous forme d'un élément XML.
     * @param doc Document XML dans lequel doit se trouver le compte sérialisé.
     * @return Le compte sous forme d'un élément XML.
     */
    QDomElement serialiser(QDomDocument& doc) const override;
    void debiter(double montant) override;
    void crediter(double montant) override;
};

#endif // COMPTE_H
