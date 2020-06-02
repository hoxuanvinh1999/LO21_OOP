#ifndef COMPTEABSTRAIT_H
#define COMPTEABSTRAIT_H

#include <QSet>
#include <QString>
#include "ISerialisable.h"
#include "ClasseCompte.h"
#include "TypeCompte.h"

using namespace std;

class CompteRacine;

class CompteAbstrait : public ISerialisable {
private:
    QSet<CompteAbstrait*> comptesEnfants;
    QString nom;
    ClasseCompte classe;
    CompteAbstrait* parent;
public:
    CompteAbstrait() = delete;
    CompteAbstrait(const CompteAbstrait& compte) = delete;
    CompteAbstrait& operator=(const CompteAbstrait& compte) = delete;
    CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent = nullptr);
    virtual ~CompteAbstrait();
    const QString& getNom() const { return nom; }
    const ClasseCompte& getClasse() const { return classe; }
    CompteAbstrait* getParent() const { return parent; }
    QList<CompteAbstrait*> getComptesEnfants() const { return comptesEnfants.values(); }
    virtual double getSolde() const;
    virtual double getSoldeRapprochement() const;
    QDomElement serialiser(QDomDocument& owner) const override;
    virtual TypeCompte getType() const = 0;
};

#endif // COMPTEABSTRAIT_H
