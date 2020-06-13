#include "Compte.h"
#include "CompteException.h"

Compte::Compte(const QString& nom, CompteAbstrait* parent): CompteAbstrait(nom, parent->getClasse(), parent), solde(0) {
    if(parent->getType() != VIRTUEL)
        throw CompteException("Le parent du compte doit etre un compte virtuel !");
}

Compte::Compte(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine): CompteAbstrait(nom, classe, racine), solde(0) {
    if(classe == AUCUN)
        throw CompteException("Le compte doit posseder une classe !");
    if(racine->getType() != RACINE)
        throw CompteException("Le parent du compte doit etre un compte racine !");

}

void Compte::crediter(double montant) {
    if(montant <= 0)
        throw CompteException("Le montant a ajouter ne peut pas etre negatif ou nul !");
    if(getClasse() == ACTIF || getClasse() == DEPENSE) {
        solde -= montant;
    } else {
        solde += montant;
    }
}

void Compte::debiter(double montant) {
    if(montant <= 0)
        throw CompteException("Le montant a retirer ne peut pas etre negatif ou nul !");
    if(getClasse() == ACTIF || getClasse() == DEPENSE) {
        solde += montant;
    } else {
        solde -= montant;
    }
}

QDomElement Compte::serialiser(QDomDocument& doc) const {
    QDomElement compteXml = CompteAbstrait::serialiser(doc);
    compteXml.setAttribute("solde", QString::number(solde, 'f', 2));
    return compteXml;
}
