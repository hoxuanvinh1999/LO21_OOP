#ifndef COMPTABILITEMANAGER_H
#define COMPTABILITEMANAGER_H

#include <QObject>
#include <QHash>
#include "ISerialisable.h"
#include "CompteRacine.h"
#include "CompteVirtuel.h"
#include "Compte.h"
#include "Transaction.h"
#include "ConstReferenceIteratorProxy.h"


class ComptabiliteManager : public QObject {

    Q_OBJECT

private:
    QString nomFichier;
    CompteRacine* compteRacine;
    QHash<QString, CompteAbstrait*> mapComptes;
    QHash<QString, Transaction*> mapTransactions;
    struct Handler {
        ComptabiliteManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    ComptabiliteManager(const QString& nomFichier);
    CompteAbstrait& getCompteParNom(const QString& nom) const;

public:
    typedef ConstReferenceIteratorProxy<QList, CompteAbstrait> const_iterator_proxy;
    ComptabiliteManager(const ComptabiliteManager&) = delete;
    ComptabiliteManager& operator=(const ComptabiliteManager&) = delete;
    ~ComptabiliteManager();
    static ComptabiliteManager& charger(const QString& nomFichier = QString());
    static ComptabiliteManager& getInstance();
    static void libererInstance();
    static bool estInstancie();
    const QString& getNomFichier() const { return nomFichier; }
    const CompteRacine& getCompteRacine() const { return *compteRacine; }
    bool existeCompte(const QString& nom) const { return mapComptes.contains(nom); }
    const_iterator_proxy comptes() const { return mapComptes.values(); }
    const CompteAbstrait& getCompte(const QString& nom) const { return getCompteParNom(nom); }
    const CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel);
    const CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel);
    void sauvegarder(const QString& nomFichier);
    void sauvegarder() const;

signals:
    void comptesModifies();
};

#endif // COMPTABILITEMANAGER_H
