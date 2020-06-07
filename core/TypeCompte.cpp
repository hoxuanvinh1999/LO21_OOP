#include "TypeCompte.h"

TypeCompte getTypeCompte(const QString& nom) {
    for(uint i = 0; i < NombreTypesComptes; ++i) {
        QString nomTypeCompte = NomsTypeCompte[i];
        if(nomTypeCompte.toUpper() == nom.toUpper()) {
            return static_cast<TypeCompte>(i);
        }
    }
    throw TypeCompteException("Le type de compte " + nom + " n'existe pas !");
}
