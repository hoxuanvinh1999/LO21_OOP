#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDate>
#include <QString>

class Transaction {
private:
    QDate date;
    QString reference;
    QString memo;
    bool figee;
public:
    Transaction(const QDate& date, const QString& reference, const QString& memo): date(date), reference(reference), memo(memo), figee(false) {}
    const QDate& getDate() const { return date; }
    const QString& getReference() const { return reference; }
    const QString& getMemo() const { return memo; }
    bool estFigee() const { return figee; }
};

#endif // TRANSACTION_H
