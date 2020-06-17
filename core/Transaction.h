#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ISerialisable.h"
#include <QDate>
#include "Operation.h"
#include "ReferenceIterator.h"

/**
 * @class Transaction
 * @brief Classe représentant une transaction composée d'opérations entre plusieurs comptes.
 */
class Transaction : public ISerialisable {
private:
    /**
     * @brief Date de la transaction.
     */
    QDate date;
    /**
     * @brief Référence de la transaction.
     */
    QString reference;
    /**
     * @brief Intitule de la transaction.
     */
    QString intitule;
    /**
     * @brief Opérations de la transactions.
     */
    QList<Operation*> operations;
    /**
     * @brief Booléen indiquant si la transaction est figée ou non.
     */
    bool figee;
    /**
     * @brief Vérifie si les opérations données sont valides.
     * @param operations Liste des opérations à vérifier.
     */
    void verifierOperations(const QList<Operation>& operations) const;
    /**
     * @brief Ajoute des opérations à la liste des opérations de la transaction.
     * @param operations Liste des opérations à ajouter à la transaction.
     */
    void ajouterOperations(const QList<Operation>& operations);
    /**
     * @brief Vide la transaction de l'ensemble de ses transactions.
     */
    void viderOperations();
public:
    /**
     * @typedef iterator
     * @brief Itérateur sur les opérations de la transaction.
     */
    using iterator = reference_iterator<QList<Operation*>::iterator>;
    /**
     * @typedef const_iterator
     * @brief Itérateur sur les opérations constantes de la transaction.
     */
    using const_iterator = reference_iterator<QList<Operation*>::const_iterator>;
    /**
     * @brief Récupère l'itérateur du début de parcours des opérations de la transaction.
     * @return L'itérateur du début de parcours des opérations de la transaction.
     */
    iterator begin() { return operations.begin(); }
    /**
     * @brief Récupère l'itérateur de fin de parcours des opérations de la transaction.
     * @return L'itérateur de fin de parcours des opérations de la transaction.
     */
    iterator end() { return operations.end(); }
    /**
     * @brief Récupère l'itérateur du début de parcours des opérations constantes de la transaction.
     * @return L'itérateur du début de parcours des opérations constantes de la transaction.
     */
    const_iterator begin() const { return operations.cbegin(); }
    /**
     * @brief Récupère l'itérateur de fin de parcours des opérations constantes de la transaction.
     * @return L'itérateur de fin de parcours des opérations constantes de la transaction.
     */
    const_iterator end() const { return operations.cend(); }
    /**
     * @brief Récupère l'itérateur du début de parcours des opérations constantes de la transaction.
     * @return L'itérateur du début de parcours des opérations constantes de la transaction.
     */
    const_iterator cbegin() const { return operations.cbegin(); }
    /**
     * @brief Récupère l'itérateur de fin de parcours des opérations constantes de la transaction.
     * @return L'itérateur de fin de parcours des opérations constantes de la transaction.
     */
    const_iterator cend() const { return operations.cend(); }
    Transaction() = delete;
    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    /**
     * @brief Constructeur d'une transaction.
     * @param date Date de la transaction.
     * @param reference Référence de la transaction.
     * @param intitule Intitulé de la transaction.
     * @param operations Liste des opérations de la transaction.
     */
    Transaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations);
    /**
      * @brief Destructeur d'une transaction.
      */
    ~Transaction();
    /**
     * @brief Récupère la date de la transaction.
     * @return La date de la transaction.
     */
    const QDate& getDate() const { return date; }
    /**
     * @brief Récupère la référence de la transaction.
     * @return La référence de la transaction.
     */
    const QString& getReference() const { return reference; }
    /**
     * @brief Récupère l'intitulé de la transaction.
     * @return L'intitulé de la transaction.
     */
    const QString& getIntitule() const { return intitule; }
    /**
     * @brief Indique si la transaction est figée ou non.
     * @return Vrai si la transaction est figée, faux sinon.
     */
    bool estFigee() const { return figee; }
    /**
     * @brief Fige la transaction.
     */
    void figer();
    /**
     * @brief Indique si la transaction implique un compte donné ou non.
     * @param nomCompte Nom du compte dont on veut savoir si il est impliqué ou non.
     * @return Vrai si le compte est impliqué dans la transaction, faux sinon.
     */
    bool impliqueCompte(const QString& nomCompte) const;
    /**
     * @brief Récupère l'opération associée à un compte donné.
     * @param nomCompte Nom du compte dont on veut récupérer l'opération.
     * @return L'opération associée au compte.
     */
    const Operation& getOperation(const QString& nomCompte) const;
    /**
     * @brief Modifie la transaction à partir de nouvelles valeurs.
     * @param nouvelleDate La nouvelle date de la transaction.
     * @param nouvelIntitule Le nouvel intitulé de la transaction.
     * @param nouvellesOperations La liste des nouvelles opérations de la transaction.
     */
    void modifier(const QDate& nouvelleDate, const QString& nouvelIntitule, const QList<Operation>& nouvellesOperations);
    /**
     * @brief Sérialise la transaction sous forme d'un élément XML.
     * @param doc Document XML dans lequel doit se trouver la transaction sérialisée.
     * @return La transaction sous forme d'un élément XML.
     */
    QDomElement serialiser(QDomDocument &doc) const override;
};

#endif // TRANSACTION_H
