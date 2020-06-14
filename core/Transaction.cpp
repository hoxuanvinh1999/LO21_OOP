#include "Transaction.h"
#include "TransactionException.h"

Transaction::Transaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations): date(date), reference(reference), intitule(intitule), figee(false) {
    if(date.isNull() || !date.isValid())
        throw TransactionException("La date de la transaction ne peut pas être nulle ou invalide !");
    if(reference.isNull() || reference.trimmed().isEmpty())
        throw TransactionException("La référence de la transaction ne peut pas être vide !");
    if(intitule.isNull() || intitule.trimmed().isEmpty())
        throw TransactionException("L'intitulé de la transaction ne peut pas être vide !");
    verifierOperations(operations);
    ajouterOperations(operations);
}

Transaction::~Transaction() {
    for(Operation* operation : operations) {
        delete operation;
    }
}

void Transaction::verifierOperations(const QList<Operation>& operations) const {
    if(operations.size() < 2)
        throw TransactionException("La transaction doit se faire entre 2 comptes ou plus !");
    double solde = 0;
    QSet<QString> comptesConcernes;
    for(const Operation& operation : operations) {
        const QString& compteConcerne = operation.getNomCompte();
        if(comptesConcernes.contains(compteConcerne))
            throw TransactionException("Le compte " + compteConcerne + " ne peut pas être présent dans plusieurs opérations au sein d'une même transaction !");
        double montant = operation.getMontant();
        TypeOperation type = operation.getType();
        if(type == DEBIT) {
            solde += montant;
        } else {
            solde -= montant;
        }
        comptesConcernes.insert(compteConcerne);
    }
    if(solde != 0)
        throw TransactionException("La somme des débits et des crédits de la transaction ne sont pas égaux !");
}

void Transaction::ajouterOperations(const QList<Operation>& operations) {
    for(const Operation& operation : operations) {
        this->operations.append(new Operation(operation));
    }
}

void Transaction::viderOperations() {
    for(Operation* operation : operations) {
        delete operation;
    }
    operations.clear();
}

void Transaction::figer() {
    if(figee)
        throw TransactionException("La transaction est déjà figée !");
    figee = true;
}

bool Transaction::impliqueCompte(const QString& nomCompte) const {
    for(const Operation* operation : operations) {
        if(operation->getNomCompte() == nomCompte)
            return true;
    }
    return false;
}

const Operation& Transaction::getOperation(const QString& nomCompte) const {
    for(const Operation* operation : operations) {
        if(operation->getNomCompte() == nomCompte)
            return *operation;
    }
    throw TransactionException("Aucune opération n'est associée au compte " + nomCompte + " !");
}

void Transaction::modifier(const QDate& nouvelleDate, const QString& nouvelIntitule, const QList<Operation>& nouvellesOperations) {
    if(figee)
        throw TransactionException("La transaction est figée et ne peut donc pas être modifiée !");
    if(nouvelleDate.isNull() || !nouvelleDate.isValid())
        throw TransactionException("La date de la transaction ne peut pas être nulle ou invalide !");
    if(nouvelIntitule.isNull() || nouvelIntitule.trimmed().isEmpty())
        throw TransactionException("L'intitulé de la transaction ne peut pas être vide !");
    verifierOperations(nouvellesOperations);
    date = nouvelleDate;
    intitule = nouvelIntitule;
    viderOperations();
    ajouterOperations(nouvellesOperations);
}

QDomElement Transaction::serialiser(QDomDocument& doc) const {
    QDomElement transactionXml = doc.createElement("Transaction");
    transactionXml.setAttribute("date", date.toString(Qt::LocalDate));
    transactionXml.setAttribute("reference", reference);
    transactionXml.setAttribute("intitule", intitule);
    for(const Operation* operation : operations) {
        QDomElement operationXml = operation->serialiser(doc);
        transactionXml.appendChild(operationXml);
    }
    return transactionXml;
}
