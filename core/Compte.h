#ifndef COMPTE_H
#define COMPTE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "CompteRacine.h"

/**
 * @brief Classe compte
 */
class Compte : public CompteAbstrait {
private:
    double solde;
public:
    Compte(const QString& nom, CompteAbstrait* parent);
    Compte(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine);
    double getSolde() const override { return solde; }
    TypeCompte getType() const override { return SIMPLE; }
    QDomElement serialiser(QDomDocument& doc) const override;
    void crediter(double montant) override;
    void debiter(double montant) override;

};

#endif // COMPTE_H
