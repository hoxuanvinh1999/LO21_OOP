#ifndef COMPTEABSTRAIT_H
#define COMPTEABSTRAIT_H

#include <QList>
#include <QString>
#include <QDate>
#include "ISerialisable.h"
#include "ClasseCompte.h"
#include "TypeCompte.h"
#include "ReferenceIterator.h"
#include "ConstReferenceIterator.h"

class CompteRacine;

/**
 * @class CompteAbstrait
 * @brief Classe abstraite représentant un compte en général.
 */
class CompteAbstrait : public ISerialisable {
private:
    /**
     * @brief Liste des enfants du compte.
     */
    QList<CompteAbstrait*> comptesEnfants;
    /**
     * @brief Nom du compte.
     */
    QString nom;
    /**
     * @brief Classe du compte.
     */
    ClasseCompte classe;
    /**
     * @brief Possible parent du compte.
     */
    CompteAbstrait* parent;
    /**
     * @brief Date du dernier rapprochement du compte.
     */
    QDate dateDernierRapprochement;
    /**
     * @brief Solde au dernier rapprochement du compte.
     */
    double soldeDernierRapprochement;
public:
    /**
     * @typedef iterator
     * @brief Itérateur sur les comptes enfants du compte.
     */
    using iterator = ReferenceIterator<QList<CompteAbstrait*>>;
    /**
     * @typedef const_iterator
     * @brief Itérateur sur les comptes enfants constants du compte.
     */
    using const_iterator = ConstReferenceIterator<QList<CompteAbstrait*>>;
    /**
     * @brief Récupère l'itérateur du début de parcours des comptes enfants du compte.
     * @return L'itérateur du début de parcours des comptes enfants du compte.
     */
    iterator begin() { return comptesEnfants.begin(); }
    /**
     * @brief Récupère l'itérateur de fin de parcours des comptes enfants du compte.
     * @return L'itérateur de fin de parcours des comptes enfants du compte.
     */
    iterator end() { return comptesEnfants.end(); }
    /**
     * @brief Récupère l'itérateur de début de parcours des comptes enfants constants du compte.
     * @return L'itérateur de début de parcours des comptes enfants constants du compte.
     */
    const_iterator begin() const { return comptesEnfants.cbegin(); }
    /**
     * @brief Récupère l'itérateur de fin de parcours des comptes enfants constants du compte.
     * @return L'itérateur de fin de parcours des comptes enfants constants du compte.
     */
    const_iterator end() const { return comptesEnfants.cend(); }
    /**
     * @brief Récupère l'itérateur de début de parcours des comptes enfants constants du compte.
     * @return L'itérateur de début de parcours des comptes enfants constants du compte.
     */
    const_iterator cbegin() const { return comptesEnfants.cbegin(); }
    /**
     * @brief Récupère l'itérateur de fin de parcours des comptes enfants constants du compte.
     * @return L'itérateur de fin de parcours des comptes enfants constants du compte.
     */
    const_iterator cend() const { return comptesEnfants.cend(); }
    CompteAbstrait() = delete;
    CompteAbstrait(const CompteAbstrait&) = delete;
    CompteAbstrait& operator=(const CompteAbstrait&) = delete;
    /**
     * @brief Constructeur d'un compte abstrait.
     * @param nom Nom du compte.
     * @param classe Classe du compte.
     * @param parent Parent du compte.
     */
    CompteAbstrait(const QString& nom, const ClasseCompte& classe, CompteAbstrait* parent = nullptr);
    /**
     * @brief Destructeur du compte abstrait.
     */
    virtual ~CompteAbstrait();
    /**
     * @brief Récupère le nom du compte.
     * @return Le nom du compte.
     */
    const QString& getNom() const { return nom; }
    /**
     * @brief Récupère la classe du compte.
     * @return La classe du compte.
     */
    const ClasseCompte& getClasse() const { return classe; }
    /**
     * @brief Récupère le parent constant du compte si il existe ou nullptr sinon.
     * @return Le parent constant du compte si il existe ou nullptr sinon.
     */
    const CompteAbstrait* getParent() const { return parent; }
    /**
     * @brief Récupère le parent du compte si il existe ou nullptr sinon.
     * @return Le parent du compte si il existe ou nullptr sinon.
     */
    CompteAbstrait* getParent() { return parent; }
    /**
     * @brief Récupère la date du dernier rapprochement du compte si il y en a une ou renvoi une QDate nulle sinon.
     * @return La date du dernier rapprochement du compte si il y en a une ou une QDate nulle sinon.
     */
    const QDate& getDateDernierRapprochement() const { return dateDernierRapprochement; }
    /**
     * @brief Récupère le solde au dernier rapprochement du compte.
     * @return Le solde au dernier rapprochement du compte.
     */
    double getSoldeDernierRapprochement() const { return soldeDernierRapprochement; }
    /**
     * @brief Récupère le niveau de profondeur du compte par rapport au compte racine.
     * @return Le niveau de profondeur du compte par rapport au compte racine.
     */
    int getNiveauProfondeur() const { return (parent ? parent->getNiveauProfondeur() + 1 : 0); }
    /**
     * @brief Récupère une courte description du compte sous forme d'une chaine de caractères.
     * @return Une courte description du compte sous forme d'une chaine de caractères.
     */
    QString toString() const { return QString(NomsClasseCompte[classe].at(0)).toUpper() + ":" + nom; }
    /**
     * @brief Rapproche le compte à une date donnée pour un solde donné.
     * @param dateRapprochement Date à laquelle rapprocher le compte.
     * @param soldeRapprochement Solde du compte au rapprochement.
     */
    void rapprocher(const QDate& dateRapprochement, double soldeRapprochement);
    /**
     * @brief Débite le compte d'un montant donné.
     * @param montant Montant à débiter au compte.
     */
    virtual void debiter(double montant) = 0;
    /**
     * @brief Crédite le compte d'un montant donné.
     * @param montant Montant à créditer au compte.
     */
    virtual void crediter(double montant) = 0;
    /**
     * @brief Récupère le solde du compte.
     * @return Le solde du compte.
     */
    virtual double getSolde() const = 0;
    /**
     * @brief Récupère le type du compte.
     * @return Le type du compte.
     */
    virtual TypeCompte getType() const = 0;
    /**
     * @brief Sérialise le compte sous forme d'un élément XML.
     * @param doc Document XML dans lequel doit se trouver le compte sérialisé.
     * @return Le compte sous forme d'un élément XML.
     */
    QDomElement serialiser(QDomDocument& doc) const override;
};

#endif // COMPTEABSTRAIT_H
