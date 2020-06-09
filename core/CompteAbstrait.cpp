#include <QDebug>
#include "CompteAbstrait.h"
#include "CompteException.h"
#include "CompteRacine.h"

CompteAbstrait::CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent): nom(nom), classe(classe), parent(parent) {
    if(nom.trimmed().isEmpty())
        throw CompteException("Le nom du compte ne peut pas être vide !");
    if(parent) {
        parent->comptesEnfants.append(this);
    }
    qDebug() << "Construction du compte " << nom;
}

CompteAbstrait::~CompteAbstrait() {
    if(parent) {
        parent->comptesEnfants.removeAt(parent->comptesEnfants.indexOf(this));
    }
    for(CompteAbstrait* compteEnfant : comptesEnfants) {
        compteEnfant->parent = nullptr;
        delete compteEnfant;
    }
    qDebug() << "Destruction du compte " << nom;
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
