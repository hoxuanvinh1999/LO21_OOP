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

bool transactionsLesserCompare(const Transaction* t1, const Transaction* t2);


class ComptabiliteManager : public QObject {

    Q_OBJECT

private:
    QString nomFichier;
    CompteRacine compteRacine;
    QHash<QString, CompteAbstrait*> mapComptes;
    QHash<QString, Transaction*> mapTransactions;
    bool sauvegarde;
    struct Handler {
        ComptabiliteManager* instance;
        Handler(): instance(nullptr) {}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    ComptabiliteManager(const QString& nomFichier);
    void chargerDonnees();
    void chargerComptes(const QDomDocument& doc);
    void chargerTransactions(const QDomDocument& doc);
    void sauvegarderComptes(QDomDocument& doc) const;
    void sauvegarderCompteEtEnfants(QDomDocument& doc, QDomElement& comptesXml, const CompteAbstrait& compte) const;
    void sauvegarderTransactions(QDomDocument& doc) const;
    void ajouterCompte(CompteAbstrait* compte);
    CompteAbstrait& getCompteParNom(const QString& nom) const;
    void ajouterTransaction(Transaction* transaction);
    Transaction& getTransactionParReference(const QString& reference) const;
    void verifierOperations(const QList<Operation>& operations) const;
    void appliquerTransaction(const Transaction* transaction);
    void annulerTransaction(const Transaction* transaction);

public:
    typedef ConstReferenceIteratorProxy<QList, CompteAbstrait> comptes_iterator_proxy;
    typedef ConstReferenceIteratorProxy<QList, Transaction> transactions_iterator_proxy;
    ComptabiliteManager() = delete;
    ComptabiliteManager(const ComptabiliteManager&) = delete;
    ComptabiliteManager& operator=(const ComptabiliteManager&) = delete;
    static ComptabiliteManager& charger(const QString& nomFichier = QString());
    static ComptabiliteManager& getInstance();
    static void libererInstance();
    static bool estInstancie();
    const QString& getNomFichier() const { return nomFichier; }
    const CompteRacine& getCompteRacine() const { return compteRacine; }
    bool estSauvegarde() const { return sauvegarde; }
    bool existeCompte(const QString& nom) const { return mapComptes.contains(nom); }
    comptes_iterator_proxy comptes() const { return mapComptes.values(); }
    const CompteAbstrait& getCompte(const QString& nom) const { return getCompteParNom(nom); }
    bool existeTransaction(const QString& reference) const { return mapTransactions.contains(reference); }
    transactions_iterator_proxy transactions() const;
    const Transaction& getTransaction(const QString& reference) const { return getTransactionParReference(reference); }
    transactions_iterator_proxy getTransactionsCompte(const QString& nom) const;
    const CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel);
    const CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel);
    const Transaction& ajouterTransaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations);
    void sauvegarder(const QString& nomFichier);
    void sauvegarder();

signals:
    void compteAjoute(const QString& nomCompte);
    void transactionAjoutee(const QString& referenceTransaction);
    void compteModifie(const QString& nomCompte);
    void transactionModifiee(const QString& referenceTransaction);
};

#endif // COMPTABILITEMANAGER_H
