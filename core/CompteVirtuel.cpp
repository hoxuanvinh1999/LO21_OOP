#include "CompteVirtuel.h"
#include "CompteRacine.h"
#include "CompteException.h"

CompteVirtuel::CompteVirtuel(const QString& nom, CompteAbstrait* parent): CompteAbstrait(nom, parent->getClasse(), parent) {
    if(parent->getType() != VIRTUEL)
        throw CompteException("Le parent du compte virtuel doit etre un compte virtuel !");
}

CompteVirtuel::CompteVirtuel(const QString& nom, const ClasseCompte& classe, CompteAbstrait* racine): CompteAbstrait(nom, classe, racine) {
    if(classe == AUCUN)
        throw CompteException("Le compte virtuel doit posseder une classe !");
    if(racine->getType() != RACINE)
        throw CompteException("Le parent du compte virtuel doit etre un compte racine !");
}


double CompteVirtuel::getSolde() const {
    double solde = 0;
    for(const CompteAbstrait& compteEnfant : *this) {
        solde += compteEnfant.getSolde();
    }
    return solde;
}
