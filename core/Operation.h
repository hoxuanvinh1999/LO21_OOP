#ifndef OPERATION_H
#define OPERATION_H

#include "ISerialisable.h"
#include "TypeOperation.h"
#include "Compte.h"


class Operation : public ISerialisable {
private:
    double montant;
    TypeOperation type;
    QString nomCompte;
public:
    Operation() = delete;
    Operation(double montant, const TypeOperation& type, const QString& nomCompte);
    double getMontant() const { return montant; }
    const TypeOperation& getType() const { return type; }
    const QString& getNomCompte() const { return nomCompte; }
    QDomElement serialiser(QDomDocument &doc) const override;
};

#endif // OPERATION_H
