#ifndef COMPTABILITEMANAGER_H
#define COMPTABILITEMANAGER_H

#include <QObject>
#include <QHash>
#include "ISerialisable.h"
#include "CompteRacine.h"
#include "CompteVirtuel.h"
#include "Compte.h"
#include "Transaction.h"


class ComptabiliteManager : public QObject {

    Q_OBJECT

private:
    QString filename;
    CompteRacine* compteRacine;
    QHash<QString, CompteAbstrait*> mapComptes;
    QHash<QString, Transaction*> mapTransactions;
    struct Handler {
        ComptabiliteManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    ComptabiliteManager(const QString& filename);

public:
    ComptabiliteManager(const ComptabiliteManager&) = delete;
    ComptabiliteManager& operator=(const ComptabiliteManager&) = delete;
    ~ComptabiliteManager();
    static ComptabiliteManager& charger(const QString& filename = QString());
    static ComptabiliteManager& getInstance();
    static void libererInstance();
    static bool estInstancie();
    const QString& getFilename() const { return filename; }
    CompteRacine& getCompteRacine() const { return *compteRacine; }
    bool existeCompte(const QString& nom) const { return mapComptes.contains(nom); }
    QList<CompteAbstrait*> getComptes() const { return mapComptes.values(); }
    CompteAbstrait& getCompte(const QString& nom) const;
    CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel);
    CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel);
    void sauvegarder(const QString& filename);
    void sauvegarder();

signals:
    void comptesModifies();
};

#endif // COMPTABILITEMANAGER_H
