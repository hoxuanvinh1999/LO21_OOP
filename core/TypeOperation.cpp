#include "TypeOperation.h"


TypeOperation getTypeOperation(const QString& nom) {
    for(uint i = 0; i < NombreTypesOperations; ++i) {
        QString nomTypeCompte = NomsTypeOperation[i];
        if(nomTypeCompte.toUpper() == nom.toUpper()) {
            return static_cast<TypeOperation>(i);
        }
    }
    throw TypeOperationException("Le type d'opération " + nom + " n'existe pas !");
}
