#include "ClasseCompte.h"

ClasseCompte getClasseCompte(const QString& nom) {
    for(uint i = 0; i < NombreClassesComptes; ++i) {
        QString nomClasseCompte = NomsClasseCompte[i];
        if(nomClasseCompte == nom) {
            return static_cast<ClasseCompte>(i);
        }
    }
    return AUCUN;
}
