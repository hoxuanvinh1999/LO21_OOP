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
    QHash<QString, unsigned int> mapOperations;
    bool figee;
    void verifierOperations(const QList<Operation>& operations) const;
    void ajouterOperations(const QList<Operation>& operations);
public:
    typedef ReferenceIterator<QList, Operation> iterator;
    typedef ConstReferenceIterator<QList, Operation> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    iterator begin() { return operations.begin(); }
    iterator end() { return operations.end(); }
    const_iterator begin() const { return operations.cbegin(); }
    const_iterator end() const { return operations.cend(); }
    const_iterator cbegin() const { return operations.cbegin(); }
    const_iterator cend() const { return operations.cend(); }
    const_iterator constBegin() const { return operations.cbegin(); }
    const_iterator constEnd() const { return operations.cbegin(); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }
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
    QList<QString> getComptesImpliques() const { return mapOperations.keys(); }
    const Operation& getOperation(const QString& nomCompte) const;
    QDomElement serialiser(QDomDocument &doc) const override;
};

#endif // TRANSACTION_H
