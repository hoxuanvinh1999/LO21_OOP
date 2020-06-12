#ifndef FONCTIONSOUTILS_H
#define FONCTIONSOUTILS_H

#include <QString>
#include <functional>
#include "Transaction.h"

struct CompteSoldeNiveau {
    const CompteAbstrait* compte;
    int niveau;
    double solde;
};

double getSoldeCalculeCompte(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions = [](const Transaction&) { return true; });

QList<CompteSoldeNiveau> getSoldesCompteEtEnfants(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions = [](const Transaction&) { return true; }, int niveau = 0);

#endif // FONCTIONSOUTILS_H
