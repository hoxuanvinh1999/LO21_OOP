#ifndef COMPTE_H
#define COMPTE_H

#include "CompteAbstrait.h"
#include "CompteVirtuel.h"
#include "CompteRacine.h"

class Compte : public CompteAbstrait {
private:
    double solde;
    double soldeRapprochement;
    Compte(const QString& nom, CompteAbstrait& parent);
    Compte(const QString& nom, const ClasseCompte& classe, CompteAbstrait& racine);
    friend class ComptabiliteManager;
public:
    double getSolde() const override { return solde; }
    double getSoldeRapprochement() const override { return soldeRapprochement; }
    void crediter(double montant);
    void debiter(double montant);
    QDomElement serialiser(QDomDocument& owner) const override;
    TypeCompte getType() const override { return SIMPLE; }
};

#endif // COMPTE_H
