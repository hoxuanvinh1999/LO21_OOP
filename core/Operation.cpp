#include "Operation.h"
#include "OperationException.h"

Operation::Operation(double montant, const TypeOperation& type, const QString& nomCompte): montant(montant), type(type), nomCompte(nomCompte) {
    if(montant < 0)
        throw OperationException("Le montant de l'opération ne peut pas être négatif !");
}

QDomElement Operation::serialiser(QDomDocument& doc) const {
    QDomElement operationXml = doc.createElement("Operation");
    operationXml.setAttribute("montant", QString::number(montant, 'f', 2));
    operationXml.setAttribute("type", static_cast<uint>(type));
    operationXml.setAttribute("compte", nomCompte);
    return operationXml;
}
