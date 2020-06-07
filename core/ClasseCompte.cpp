#include "ClasseCompte.h"

ClasseCompte getClasseCompte(const QString& nom) {
    for(uint i = 0; i < NombreClassesComptes; ++i) {
        QString nomClasseCompte = NomsClasseCompte[i];
        if(nomClasseCompte.toUpper() == nom.toUpper()) {
            return static_cast<ClasseCompte>(i);
        }
    }
    throw ClasseCompteException("La classe de compte " + nom + " n'existe pas !");
}
