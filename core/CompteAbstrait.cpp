#include <QDebug>
#include "CompteAbstrait.h"
#include "CompteException.h"
#include "CompteRacine.h"

CompteAbstrait::CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent): nom(nom), classe(classe), parent(parent) {
    if(nom.trimmed().isEmpty())
        throw CompteException("Le nom du compte ne peut pas etre vide !");
    if(parent) {
        parent->comptesEnfants.insert(this);
    }
    qDebug() << "Construction du compte " << nom << endl;
}

CompteAbstrait::~CompteAbstrait() {
    if(parent) {
        parent->comptesEnfants.remove(this);
    }
    for(CompteAbstrait* compte : comptesEnfants) {
        delete compte;
    }
    qDebug() << "Destruction du compte " << nom << endl;
}

double CompteAbstrait::getSolde() const {
    double solde = 0;
    for(CompteAbstrait* compteEnfant : comptesEnfants) {
        solde += compteEnfant->getSolde();
    }
    return solde;
}

QDomElement CompteAbstrait::serialiser(QDomDocument& doc) const {
    QDomElement cpt = doc.createElement("Compte");
    cpt.setAttribute("type", static_cast<uint>(getType()));
    cpt.setAttribute("nom", nom);
    cpt.setAttribute("classe", static_cast<uint>(classe));
    if(parent) {
        cpt.setAttribute("parent", parent->getNom());
    }
    return cpt;
}

double CompteAbstrait::getSoldeRapprochement() const {
    double soldeRapprochement = 0;
    for(CompteAbstrait* compteEnfant : comptesEnfants) {
        soldeRapprochement += compteEnfant->getSoldeRapprochement();
    }
    return soldeRapprochement;
}
