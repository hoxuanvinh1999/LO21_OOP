#ifndef COMPTABILITEMANAGER_H
#define COMPTABILITEMANAGER_H

#include <QObject>
#include <QVector>
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
    CompteRacine compteRacine;
    QList<CompteAbstrait*> comptes;
    QList<Transaction*> transactions;
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
    void sauvegarderComptes(QDomDocument& doc, QDomElement& racineDoc) const;
    void sauvegarderCompteEtEnfants(QDomDocument& doc, QDomElement& comptesXml, const CompteAbstrait& compte) const;
    void sauvegarderTransactions(QDomDocument& doc, QDomElement& racineDoc) const;
    void ajouterCompte(CompteAbstrait* compte);
    void supprimerCompte(CompteAbstrait* compte);
    CompteAbstrait& getCompteParNom(const QString& nomCompte);
    const CompteAbstrait& getCompteParNom(const QString& nomCompte) const;
    QSet<QString> getNomCompteEtEnfants(const CompteAbstrait* compte) const;
    bool compteEstSupprimable(const CompteAbstrait* compte) const;
    void verifierOperations(const QList<Operation>& operations) const;
    void informerModificationCompte(const CompteAbstrait* compte) const;
    void appliquerTransaction(const Transaction* transaction);
    void annulerTransaction(const Transaction* transaction);
    void ajouterTransaction(Transaction* transaction);
    void supprimerTransaction(Transaction* transaction);
    Transaction& getTransactionParReference(const QString& referenceTransaction);
    const Transaction& getTransactionParReference(const QString& referenceTransaction) const;
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
    bool existeCompte(const QString& nom) const;
    QSet<QString> getNomCompteEtEnfants(const QString& nomCompte) const;
    const CompteAbstrait& getCompte(const QString& nomCompte) const { return getCompteParNom(nomCompte); }
    comptes_iterator_proxy getComptes() const { return comptes; }
    comptes_iterator_proxy getComptesVirtuels() const;
    comptes_iterator_proxy getComptesSimples() const;
    bool compteEstSupprimable(const QString& nomCompte) const;
    bool existeTransaction(const QString& referenceTransaction) const;
    const Transaction& getTransaction(const QString& reference) const { return getTransactionParReference(reference); }
    transactions_iterator_proxy getTransactions() const { return transactions; }
    transactions_iterator_proxy getTransactionsCompte(const QString& nomCompte) const;
    const CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel);
    const CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel);
    const CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, double soldeInitial, const QString& nomCompteCapitaux);
    const CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, double soldeInitial, const QString& nomCompteCapitaux);
    const CompteAbstrait& ajouterCompteCapitaux(const QString& nom, const QString& nomParent);
    const Transaction& ajouterTransaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations);
    void supprimerCompte(const QString& nomCompte);
    void supprimerTransaction(const QString& referenceTransaction);
    void sauvegarder(const QString& nomFichier);
    void sauvegarder();

signals:
    void compteAjoute(const QString& nomCompte) const;
    void compteModifie(const QString& nomCompte) const;
    void compteSupprime(const QString& nomCompte) const;
    void transactionAjoutee(const QString& referenceTransaction) const;
    void transactionModifiee(const QString& referenceTransaction) const;
    void transactionSupprimee(const QString& referenceTransaction) const;
};

#endif // COMPTABILITEMANAGER_H
