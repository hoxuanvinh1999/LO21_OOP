#ifndef COMPTEABSTRAIT_H
#define COMPTEABSTRAIT_H

#include <QSet>
#include <QString>
#include "ISerialisable.h"
#include "ClasseCompte.h"
#include <QDate>
#include "TypeCompte.h"
#include "ReferenceIterator.h"
#include "ConstReferenceIterator.h"

using namespace std;

class CompteRacine;

/**
 * @brief Implémente les méthodes et les attributs communs à tout types de compte
 */

class CompteAbstrait : public ISerialisable {
private:
    QList<CompteAbstrait*> comptesEnfants;
    QString nom;
    ClasseCompte classe;
    CompteAbstrait* parent;
    QDate dateDernierRapprochement;
    double soldeDernierRapprochement;
public:
    using iterator = ReferenceIterator<QList<CompteAbstrait*>>;
    using const_iterator = ConstReferenceIterator<QList<CompteAbstrait*>>;
    iterator begin() { return comptesEnfants.begin(); }
    iterator end() { return comptesEnfants.end(); }
    const_iterator begin() const { return comptesEnfants.cbegin(); }
    const_iterator end() const { return comptesEnfants.cend(); }
    const_iterator cbegin() const { return comptesEnfants.cbegin(); }
    const_iterator cend() const { return comptesEnfants.cend(); }
    const_iterator constBegin() const { return comptesEnfants.cbegin(); }
    const_iterator constEnd() const { return comptesEnfants.cbegin(); }
    CompteAbstrait() = delete;
    CompteAbstrait(const CompteAbstrait&) = delete;
    CompteAbstrait& operator=(const CompteAbstrait&) = delete;
    CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent = nullptr);
    virtual ~CompteAbstrait();
    const QString& getNom() const { return nom; }
    const ClasseCompte& getClasse() const { return classe; }
    const CompteAbstrait* getParent() const { return parent; }
    CompteAbstrait* getParent() { return parent; }
    const QDate& getDateDernierRapprochement() const { return dateDernierRapprochement; }
    double getSoldeDernierRapprochement() const { return soldeDernierRapprochement; }
    int getNiveauProfondeur() const { return (parent ? parent->getNiveauProfondeur() + 1 : 0); }
    QString toString() const { return QString(NomsClasseCompte[classe].at(0)).toUpper() + ":" + nom; }
    void rapprocher(const QDate& dateRapprochement, double soldeRapprochement);
    virtual void debiter(double montant) = 0;
    virtual void crediter(double montant) = 0;
    virtual double getSolde() const = 0;
    virtual TypeCompte getType() const = 0;
    QDomElement serialiser(QDomDocument& doc) const override;
};

#endif // COMPTEABSTRAIT_H
