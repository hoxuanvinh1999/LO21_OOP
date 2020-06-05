#ifndef COMPTEABSTRAIT_H
#define COMPTEABSTRAIT_H

#include <QSet>
#include <QString>
#include "ISerialisable.h"
#include "ClasseCompte.h"
#include "TypeCompte.h"
#include "ReferenceIterator.h"
#include "ConstReferenceIterator.h"

using namespace std;

class CompteRacine;

class CompteAbstrait : public ISerialisable {
private:
    QSet<CompteAbstrait*> comptesEnfants;
    QString nom;
    ClasseCompte classe;
    CompteAbstrait* parent;
public:
    typedef ReferenceIterator<QSet, CompteAbstrait> iterator;
    typedef ConstReferenceIterator<QSet, CompteAbstrait> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    iterator begin() { return comptesEnfants.begin(); }
    iterator end() { return comptesEnfants.end(); }
    const_iterator begin() const { return comptesEnfants.cbegin(); }
    const_iterator end() const { return comptesEnfants.cend(); }
    const_iterator cbegin() const { return comptesEnfants.cbegin(); }
    const_iterator cend() const { return comptesEnfants.cend(); }
    const_iterator constBegin() const { return comptesEnfants.cbegin(); }
    const_iterator constEnd() const { return comptesEnfants.cbegin(); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }
    CompteAbstrait() = delete;
    CompteAbstrait(const CompteAbstrait&) = delete;
    CompteAbstrait& operator=(const CompteAbstrait&) = delete;
    CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent = nullptr);
    virtual ~CompteAbstrait();
    const QString& getNom() const { return nom; }
    const ClasseCompte& getClasse() const { return classe; }
    const CompteAbstrait* getParent() const { return parent; }
    CompteAbstrait* getParent() { return parent; }
    QString toString() const { return QString(NomsClasseCompte[classe].at(0)).toUpper() + ":" + nom; }
    virtual void debiter(double) {}
    virtual void crediter(double) {}
    virtual double getSolde() const;
    virtual double getSoldeRapprochement() const;
    QDomElement serialiser(QDomDocument& doc) const override;
    virtual TypeCompte getType() const = 0;
};

#endif // COMPTEABSTRAIT_H
