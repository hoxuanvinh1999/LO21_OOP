#ifndef OPERATION_H
#define OPERATION_H

#include "TypeOperation.h"
#include "Compte.h"


class Operation {
private:
    double montant;
    TypeOperation type;
    const Compte& compte;
public:
    Operation(double montant, const TypeOperation& type, const Compte& compte);
    double getMontant() const { return montant; }
    const TypeOperation& getType() const { return type; }
    const Compte& getCompte() const { return compte; }
};

#endif // OPERATION_H
