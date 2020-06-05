#include "Operation.h"
#include "OperationException.h"

Operation::Operation(double montant, const TypeOperation& type, const QString& nomCompte): montant(montant), type(type), nomCompte(nomCompte) {
    if(montant <= 0)
        throw OperationException("Le montant de l'opération ne peut pas être négatif ou nul !");
}

QDomElement Operation::serialiser(QDomDocument& doc) const {
    QDomElement operationXml = doc.createElement("Operation");
    operationXml.setAttribute("montant", montant);
    operationXml.setAttribute("type", static_cast<uint>(type));
    operationXml.setAttribute("compte", nomCompte);
    return operationXml;
}
