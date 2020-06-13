#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ISerialisable.h"
#include <QDate>
#include "Operation.h"
#include "ReferenceIterator.h"
#include "ConstReferenceIterator.h"

class Transaction : public ISerialisable {
private:
    QDate date;
    QString reference;
    QString intitule;
    QList<Operation*> operations;
    bool figee;
    void verifierOperations(const QList<Operation>& operations) const;
    void ajouterOperations(const QList<Operation>& operations);
    void viderOperations();
public:
    using iterator = ReferenceIterator<QList<Operation*>>;
    using const_iterator = ConstReferenceIterator<QList<Operation*>>;
    iterator begin() { return operations.begin(); }
    iterator end() { return operations.end(); }
    const_iterator begin() const { return operations.cbegin(); }
    const_iterator end() const { return operations.cend(); }
    const_iterator cbegin() const { return operations.cbegin(); }
    const_iterator cend() const { return operations.cend(); }
    const_iterator constBegin() const { return operations.cbegin(); }
    const_iterator constEnd() const { return operations.cbegin(); }
    Transaction() = delete;
    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    Transaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations);
    ~Transaction();
    const QDate& getDate() const { return date; }
    const QString& getReference() const { return reference; }
    const QString& getIntitule() const { return intitule; }
    bool estFigee() const { return figee; }
    void figer();
    bool impliqueCompte(const QString& nomCompte) const;
    const Operation& getOperation(const QString& nomCompte) const;
    void modifier(const QDate& nouvelleDate, const QString& nouvelIntitule, const QList<Operation>& nouvellesOperations);
    QDomElement serialiser(QDomDocument &doc) const override;
};

#endif // TRANSACTION_H
