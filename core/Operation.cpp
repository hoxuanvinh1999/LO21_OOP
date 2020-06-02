#include "Operation.h"
#include "OperationException.h"

Operation::Operation(double montant, const TypeOperation& type, const Compte& compte): montant(montant), type(type), compte(compte) {
    if(montant <= 0)
        throw OperationException("Le montant de l'operation ne peut pas etre negatif ou nul !");
}
