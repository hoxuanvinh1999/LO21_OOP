#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "ISerialisable.h"
#include <QDate>
#include "Operation.h"
#include "ConstReferenceIteratorProxy.h"

class Transaction : public ISerialisable {
private:
    QDate date;
    QString reference;
    QString intitule;
    QHash<QString, Operation*> mapOperations;
    bool figee;
    void verifierOperations(const QList<Operation>& operations) const;
    void ajouterOperations(const QList<Operation>& operations);
public:
    typedef ConstReferenceIteratorProxy<QList, Operation> operations_iterator_proxy;
    operations_iterator_proxy operations() const { return mapOperations.values(); }
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
    bool impliqueCompte(const QString& nomCompte) const { return mapOperations.contains(nomCompte); }
    const Operation& getOperation(const QString& nomCompte) const;
    QDomElement serialiser(QDomDocument &doc) const override;
};

#endif // TRANSACTION_H
