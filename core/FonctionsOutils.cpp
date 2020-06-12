#include "FonctionsOutils.h"
#include "ComptabiliteManager.h"

double getSoldeCalculeCompte(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions) {
    double solde = 0;
    ComptabiliteManager& manager = ComptabiliteManager::getInstance();
    const CompteAbstrait& compte = manager.getCompte(nomCompte);
    for(const Transaction& transaction : manager.getTransactionsCompte(nomCompte)) {
        if(filtreurTransactions(transaction)) {
            const Operation& operation = transaction.getOperation(nomCompte);
            if(operation.getType() == DEBIT) {
                solde += operation.getMontant();
            } else {
                solde -= operation.getMontant();
            }
        }
    }
    if(compte.getClasse() == PASSIF || compte.getClasse() == RECETTE) {
        solde = -solde;
    }
    return solde;
}

QList<CompteSoldeNiveau> getSoldesCompteEtEnfants(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions, int niveau) {
    QList<CompteSoldeNiveau> soldesComptes;
    double soldeCompte = 0;
    if(compte.getType() == SIMPLE) {
        soldeCompte = getSoldeCalculeCompte(compte.getNom(), filtreurTransactions);
    } else {
        for(const CompteAbstrait& compteEnfant : compte) {
            QList<CompteSoldeNiveau> soldesComptesEnfants = getSoldesCompteEtEnfants(compteEnfant, filtreurTransactions, niveau + 1);
            soldeCompte += soldesComptesEnfants.first().solde;
            soldesComptes.append(soldesComptesEnfants);
        }
    }
    soldesComptes.push_front({&compte, niveau, soldeCompte});
    return soldesComptes;
}
