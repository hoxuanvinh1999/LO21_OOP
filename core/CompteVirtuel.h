#ifndef COMPTEVIRTUEL_H
#define COMPTEVIRTUEL_H

#include "CompteAbstrait.h"

class CompteRacine;

class CompteVirtuel : public CompteAbstrait {
private:
    CompteVirtuel(const QString& nom, CompteAbstrait& parent);
    CompteVirtuel(const QString& nom, const ClasseCompte& classe, CompteAbstrait& racine);
    friend class ComptabiliteManager;
public:
    TypeCompte getType() const override { return VIRTUEL; }
};

#endif // COMPTEVIRTUEL_H
