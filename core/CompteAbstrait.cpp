#include <QDebug>
#include "CompteAbstrait.h"
#include "CompteException.h"
#include "CompteRacine.h"

CompteAbstrait::CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent): nom(nom), classe(classe), parent(parent), dateDernierRapprochement(), soldeDernierRapprochement(0) {
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

void CompteAbstrait::rapprocher(const QDate& dateRapprochement, double soldeRapprochement) {
    if(!dateDernierRapprochement.isNull() && dateRapprochement < dateDernierRapprochement)
        throw CompteException("La date de rapprochement precède la date du dernier rapprochement du compte !");
    dateDernierRapprochement = dateRapprochement;
    soldeDernierRapprochement = soldeRapprochement;
}

QDomElement CompteAbstrait::serialiser(QDomDocument& doc) const {
    QDomElement compteXml = doc.createElement("Compte");
    compteXml.setAttribute("type", static_cast<uint>(getType()));
    compteXml.setAttribute("nom", nom);
    compteXml.setAttribute("classe", static_cast<uint>(classe));
    if(parent) {
        compteXml.setAttribute("parent", parent->getNom());
    }
    compteXml.setAttribute("date_dernier_rapprochement", dateDernierRapprochement.toString(Qt::LocalDate));
    compteXml.setAttribute("solde_dernier_rapprochement", QString::number(soldeDernierRapprochement, 'f', 2));
    return compteXml;
}
