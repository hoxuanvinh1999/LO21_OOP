#include "CompteRacine.h"

double CompteRacine::getSolde() const {
    double solde = 0;
    for(const CompteAbstrait& compteEnfant : *this) {
        if(compteEnfant.getClasse() == ACTIF || compteEnfant.getClasse() == DEPENSE) {
            solde += compteEnfant.getSolde();
        } else {
            solde -= compteEnfant.getSolde();
        }
    }
    return solde;
}

double CompteRacine::getSoldeRapprochement() const {
    double soldeRapprochement = 0;
    for(const CompteAbstrait& compteEnfant : *this) {
        if(compteEnfant.getClasse() == ACTIF || compteEnfant.getClasse() == DEPENSE) {
            soldeRapprochement += compteEnfant.getSoldeRapprochement();
        } else {
            soldeRapprochement -= compteEnfant.getSoldeRapprochement();
        }
    }
    return soldeRapprochement;
}
