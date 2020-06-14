#ifndef COMPTABILITEMANAGER_H
#define COMPTABILITEMANAGER_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <functional>
#include "ISerialisable.h"
#include "CompteRacine.h"
#include "CompteVirtuel.h"
#include "Compte.h"
#include "Transaction.h"
#include "ConstContainerWrapper.h"
#include "ContainerWrapper.h"

using namespace std;

/**
 * @struct CompteSoldeStruct
 * @brief Structure composée du nom d'un compte et de son solde.
 */
struct CompteSoldeStruct {
    /**
     * @brief Nom du compte.
     */
    QString nomCompte;
    /**
     * @brief Solde du compte.
     */
    double solde;
};

/**
 * @class ComptabiliteManager
 * @brief Classe représentant un gestionnaire de comptabilité avec des comptes et des transactions.
 */
class ComptabiliteManager : public QObject {

    Q_OBJECT

private:
    /**
     * @brief Nom du fichier dans lequel les données de comptabilité doivent être sauvegardées.
     */
    QString nomFichier;
    /**
     * @brief Compte racine des comptes du gestionnaire de comptabilité.
     */
    CompteRacine compteRacine;
    /**
     * @brief Comptes du gestionnaire de comptabilité.
     */
    QList<CompteAbstrait*> comptes;
    /**
     * @brief Transactions du gestionnaire de comptabilité.
     */
    QList<Transaction*> transactions;
    /**
     * @brief Booléen indiquant si les dernières modifications du gestionnaire ont été sauvegardées.
     */
    bool sauvegarde;
    /**
     * @struct Handler
     * @brief Structure de gestion d'une instance du gestionnaire de comptabilité.
     */
    struct Handler {
        /**
         * @brief Instance du gestionnaire du comptabilité.
         */
        ComptabiliteManager* instance;
        /**
         * @brief Constructeur d'un handler
         */
        Handler(): instance(nullptr) {}
        /**
          * @brief Destructeur du handler
          */
        ~Handler() { delete instance; }
    };
    /**
     * @brief Instance unique de la structure de gestion de l'instance du gestionnaire de comptabilité.
     */
    static Handler handler;
    /**
     * @brief Constructeur d'un gestionnaire de comptabilité à partir d'un fichier de données.
     * @param nomFichier Nom du fichier de données à partir du quel charger le gestionnaire de comptabilité.
     */
    ComptabiliteManager(const QString& nomFichier);
    /**
     * @brief Charge les données du fichier de données du gestionnaire de comptabilité.
     */
    void chargerDonnees();
    /**
     * @brief Charge les comptes sérialisés présents dans un document XML dans le gestionnaire de comptabilité.
     * @param doc Document XML contenant des comptes sérialisés.
     */
    void chargerComptes(const QDomDocument& doc);
    /**
     * @brief Charge les transactions sérialisées présentes dans un document XML dans le gestionnaire de comptabilité.
     * @param doc Document XML contenant des transactions sérialisées.
     */
    void chargerTransactions(const QDomDocument& doc);
    /**
     * @brief Sauvegarder les comptes du gestionnaire de comptabilité à la racine d'un document XML.
     * @param doc Document XML dans lequel sauvegarder les comptes du gestionnaire de comptabilité.
     * @param racineDoc Racine du document XML à laquelle rajouter les comptes sérialisés à sauvegarder.
     */
    void sauvegarderComptes(QDomDocument& doc, QDomElement& racineDoc) const;
    /**
     * @brief Sauvegarde un compte et ses enfants dans un document XML en dessous du noeud censés contenir les comptes sérialisés.
     * @param doc Document XML dans lequel sauvegarder le compte et ses enfants.
     * @param comptesXml Noeud du Document XML devant contenir le compte et ses enfants sérialisés.
     * @param compte Compte à sauvegarder avec ses enfants dans le document XML.
     */
    void sauvegarderCompteEtEnfants(QDomDocument& doc, QDomElement& comptesXml, const CompteAbstrait& compte) const;
    /**
     * @brief Sauvegarder les transactions du gestionnaire de comptabilité à la racine d'un document XML.
     * @param doc Document XML dans lequel sauvegarder les transactions du gestionnaire de comptabilité.
     * @param racineDoc Racine du document XML à laquelle rajouter les transactions sérialisées à sauvegarder.
     */
    void sauvegarderTransactions(QDomDocument& doc, QDomElement& racineDoc) const;
    /**
     * @brief Ajoute un compte à la liste des comptes du gestionnaire de comptabilité.
     * @param compte Compte à ajouter à la liste des comptes du gestionnaire de comptabilité.
     */
    void ajouterCompte(CompteAbstrait* compte);
    /**
     * @brief Supprime un compte de la liste des comptes du gestionnaire de comptabilité.
     * @param compte Compte à supprimer de la liste des comptes du gestionnaire de comptabilité.
     */
    void supprimerCompte(CompteAbstrait* compte);
    /**
     * @brief Recupère le compte associé au nom de compte donné dans la liste des comptes du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte que l'on souhaite récupérer.
     * @return Le compte associé au nom de compte donné dans la liste des comptes du gestionnaire de comptabilité.
     */
    CompteAbstrait& getCompteParNom(const QString& nomCompte);
    /**
     * @brief Recupère le compte constant associé au nom de compte donné dans la liste des comptes du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte que l'on souhaite récupérer.
     * @return Le compte constant associé au nom de compte donné dans la liste des comptes du gestionnaire de comptabilité.
     */
    const CompteAbstrait& getCompteParNom(const QString& nomCompte) const;
    /**
     * @brief Récupère le nom d'un compte et de l'ensemble de ses enfants.
     * @param compte Compte dont on veut récupérer le nom et celui de ses enfants.
     * @return Le nom du compte et de l'ensemble de ses enfants.
     */
    QList<QString> getNomCompteEtEnfants(const CompteAbstrait* compte) const;
    /**
     * @brief Indique si un compte est supprimable ou non de la liste des comptes du gestionnaire de comptabilité.
     * @param compte Compte dont on veut savoir si il est supprimable ou non.
     * @return Vrai si le compte est supprimable de la liste des comptes du gestionnaire de comptabilité, faux sinon.
     */
    bool compteEstSupprimable(const CompteAbstrait* compte) const;
    /**
     * @brief Vérifie que les opérations et la date d'une transaction sont valides.
     * @param operations Opérations de la transaction à vérifier.
     * @param date Date de la transaction à vérifier.
     */
    void verifierOperationsEtDateTransaction(const QList<Operation>& operations, const QDate& date) const;
    /**
     * @brief Informe de la modification d'un compte.
     * @param compte Compte dont on souhaite informer la modification.
     */
    void informerModificationCompte(const CompteAbstrait* compte) const;
    /**
     * @brief Applique une transaction sur l'ensemble des comptes qu'elle implique.
     * @param transaction Transaction à appliquer.
     */
    void appliquerTransaction(const Transaction* transaction);
    /**
     * @brief Annule une transaction sur l'ensemble des comptes qu'elle implique.
     * @param transaction Transaction à annuler.
     */
    void annulerTransaction(const Transaction* transaction);
    /**
     * @brief Ajouter une transaction à la liste des transactions du gestionnaire de comptabilité.
     * @param transaction Transaction à ajouter.
     */
    void ajouterTransaction(Transaction* transaction);
    /**
     * @brief Supprime une transaction de la liste des transactions du gestionnaire de comptabilité.
     * @param transaction Transaction à supprimer.
     */
    void supprimerTransaction(Transaction* transaction);
    /**
     * @brief Récupère une transaction de la liste des transactions du gestionnaire de comptabilité à partir de sa référence.
     * @param referenceTransaction Référence de la transaction à récupérer.
     * @return La transaction récupérée à partir de sa référence dans la liste des transactions du gestionnaire de comptabilité.
     */
    Transaction& getTransactionParReference(const QString& referenceTransaction);
    /**
     * @brief Récupère une transaction constante de la liste des transactions du gestionnaire de comptabilité à partir de sa référence.
     * @param referenceTransaction Référence de la transaction à récupérer.
     * @return La transaction constante récupérée à partir de sa référence dans la liste des transactions du gestionnaire de comptabilité.
     */
    const Transaction& getTransactionParReference(const QString& referenceTransaction) const;
    /**
     * @brief Récupère la liste des transactions filtrées impliquant un compte donné dans la liste des transactions du gestionnaire de comptabilité.
     * @param compte Compte dont on souhaite récupérer les transactions filtrées.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte.
     * @return La liste des transactions filtrées impliquant le compte dans la liste des transactions du gestionnaire de comptabilité.
     */
    QList<Transaction*> getTransactionsCompte(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions);
    /**
     * @brief Récupère la liste des transactions constantes filtrées impliquant un compte donné dans la liste des transactions du gestionnaire de comptabilité.
     * @param compte Compte dont on souhaite récupérer les transactions constantes filtrées.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte.
     * @return La liste des transactions constantes filtrées impliquant le compte dans la liste des transactions du gestionnaire de comptabilité.
     */
    QList<const Transaction*> getTransactionsCompte(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions) const;
    /**
     * @brief Récupère le solde calculé d'un compte à partir d'une fonction de filtrage des transactions qui l'impliquent.
     * @param compte Compte dont on souhaite récupérer le solde calculé.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte.
     * @return Le solde calculé du compte à partir de la fonction de filtrage des transactions qui l'impliquent.
     */
    double getSoldeCalculeCompte(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions) const;
    /**
     * @brief Récupère les soldes calculés d'un compte et de l'ensemble de ses enfants à partir d'une fonction de filtrage des transactions qui les impliquent.
     * @param compte Compte dont on souhaite récupérer le solde calculé et celui de l'ensemble de ses enfants.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte et l'ensemble de ses enfants.
     * @return La liste des soldes calculés du compte et de l'ensemble de ses enfants sous forme d'une structure à partir de la fonction de filtrage des transactions qui les impliquent.
     */
    QList<CompteSoldeStruct> getSoldesCalculesCompteEtEnfants(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions) const;
    /**
     * @brief Rapproche un compte de la liste des comptes du gestionnaire de comptabilité à une date de rapprochement donné.
     * @param compte Compte à rapprocher.
     * @param dateRapprochement Date à laquelle rapprocher le compte.
     */
    void rapprocherCompte(CompteAbstrait& compte, const QDate& dateRapprochement);
public:
    /**
     * @typedef comptes_wrapper
     * @brief Wrapper d'une liste de pointeurs de comptes constants.
     */
    using comptes_wrapper = ConstContainerWrapper<QList<const CompteAbstrait*>, ConstReferenceIterator<QList<const CompteAbstrait*>>>;
    /**
     * @typedef transactions_wrapper
     * @brief Wrapper d'une liste de pointeurs de transactions constantes.
     */
    using transactions_wrapper = ConstContainerWrapper<QList<const Transaction*>, ConstReferenceIterator<QList<const Transaction*>>>;
    /**
     * @typedef comptes_soldes_wrapper
     * @brief Wrapper d'une liste de structures compte <-> solde
     */
    using comptes_soldes_wrapper = ContainerWrapper<QList<CompteSoldeStruct>>;
    /**
     * @typedef noms_comptes_wrapper
     * @brief Wrapper d'une liste de noms de comptes
     */
    using noms_comptes_wrapper = ContainerWrapper<QList<QString>>;
    ComptabiliteManager() = delete;
    ComptabiliteManager(const ComptabiliteManager&) = delete;
    ComptabiliteManager& operator=(const ComptabiliteManager&) = delete;
    /**
     * @brief Charge un nouveau gestionnaire de comptabilité à partir d'un fichier de données ou non.
     * @param nomFichier Nom du fichier de données à partir duquel charger le gestionnaire de comptabilité.
     * @return L'instance du nouveau gestionnaire de comptabilité créé.
     */
    static ComptabiliteManager& charger(const QString& nomFichier = QString());
    /**
     * @brief Récupère l'instance du gestionnaire de comptabilité.
     * @return L'instance du gestionnaire de comptabilité.
     */
    static ComptabiliteManager& getInstance();
    /**
     * @brief Libère l'instance du gestionnaire de comptabilité.
     */
    static void libererInstance();
    /**
     * @brief Indique si le gestionnaire de comptabilité est instancié ou non.
     * @return Vrai si le gestionnaire de comptabilité est instancié, faux sinon.
     */
    static bool estInstancie();
    /**
     * @brief Récupère le nom du fichier de données dans lequel le gestionnaire sera sauvegarder ou un QString nul si il n'en a pas.
     * @return Le nom du fichier de données dans lequel le gestionnaire sera sauvegarder ou un QString nul si il n'en a pas.
     */
    const QString& getNomFichier() const { return nomFichier; }
    /**
     * @brief Récupère le compte racine des comptes du gestionnaire de comptabilité.
     * @return Le compte racine des comptes du gestionnaire de comptabilité.
     */
    const CompteRacine& getCompteRacine() const { return compteRacine; }
    /**
     * @brief Indique si les dernières modifications apportées au gestionnaire de comptabilité ont été sauvegardées ou non.
     * @return Vrai si les dernières modifications apportées au gestionnaire de comptabilité ont été sauvegardées, faux sinon.
     */
    bool estSauvegarde() const { return sauvegarde; }
    /**
     * @brief Indique si le compte de nom donné existe dans la liste des comptes du gestionnaire de comptabilité ou non.
     * @param nomCompte Nom du compte dont on veut savoir si il existe ou non.
     * @return Vrai si le compte existe dans la liste des comptes du gestionnaire de comptabilité, faux sinon.
     */
    bool existeCompte(const QString& nomCompte) const;
    /**
     * @brief Récupère le nom d'un compte et de l'ensemble de ses enfants.
     * @param nomCompte Le nom du compte dont on veut également récupérer celui de ses enfants.
     * @return Le nom du compte et de l'ensemble de ses enfants.
     */
    noms_comptes_wrapper getNomCompteEtEnfants(const QString& nomCompte) const;
    /**
     * @brief Récupère un compte dans la liste des comptes du gestionnaire de comptabilité à partir de son nom.
     * @param nomCompte Nom du compte dont on veut récupérer le compte associé.
     * @return Le compte associé au nom de compte donné dans la liste des comptes du gestionnaire de comptabilité.
     */
    const CompteAbstrait& getCompte(const QString& nomCompte) const { return getCompteParNom(nomCompte); }
    /**
      * @brief Récupère les comptes filtrés de la liste des comptes du gestionnaire de comptabilité.
      * @param filtreurComptes Filtreur des comptes.
      * @return Les comptes filtrés de la liste des comptes du gestionnaire de comptabilité.
      */
    comptes_wrapper getComptes(const function<bool(const CompteAbstrait&)>& filtreurComptes = [](const CompteAbstrait&) { return true; }) const;
    /**
     * @brief Indique si un compte avec un nom donné est supprimable de la liste des comptes du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte dont on veut savoir si il est supprimable ou non.
     * @return Vrai si le compte est supprimable de la liste des comptes du gestionnaire de comptabilité, faux sinon.
     */
    bool compteEstSupprimable(const QString& nomCompte) const;
    /**
     * @brief Indique si la transaction de référence donnée existe dans la liste des transactions du gestionnaire de comptabilité.
     * @param referenceTransaction Référence de la transaction dont on veut savoir si elle existe ou non.
     * @return Vrai si la transaction existe dans la liste des comptes de gestionnaire de comptabilité, faux sinon.
     */
    bool existeTransaction(const QString& referenceTransaction) const;
    /**
     * @brief Récupère une transaction dans la liste des transactions du gestionnaire de comptabilité à partir de sa référence.
     * @param referenceTransaction Référence de la transaction dont on veut récupérer la transaction associée.
     * @return La transaction associée à la référence de transaction donnée dans la liste des transactions du gestionnaire de comptabilité.
     */
    const Transaction& getTransaction(const QString& referenceTransaction) const { return getTransactionParReference(referenceTransaction); }
    /**
      * @brief Récupère les transactions constantes filtrées de la liste des transactions du gestionnaire de comptabilité.
      * @param filtreurTransactions Filtreur des transactions.
      * @return Les transactions constantes filtrées de la liste des transactions du gestionnaire de comptabilité.
      */
    transactions_wrapper getTransactions(const function<bool(const Transaction&)>& filtreurTransactions = [](const Transaction&) { return true; }) const;
    /**
     * @brief Récupère la liste des transactions constantes filtrées impliquant un compte donné dans la liste des transactions du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte dont on souhaite récupérer les transactions constantes filtrées.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte.
     * @return Les transactions constantes filtrées impliquant le compte dans la liste des transactions du gestionnaire de comptabilité.
     */
    transactions_wrapper getTransactionsCompte(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions = [](const Transaction&) { return true; }) const;
    /**
     * @brief Ajoute un compte à partir de son nom, sa classe et le fait qu'il soit virtuel ou non sous la racine des comptes du gestionnaire de comptabilité.
     * @param nom Nom du compte à ajouter.
     * @param classe Classe du compte à ajouter.
     * @param virtuel Booléen indiquant si le compte doit être virtuel ou non.
     * @return Une référence vers le nouveau compte ajouté.
     */
    const CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel);
    /**
     * @brief Ajoute un compte à partir de son nom, un parent et le fait qu'il soit virtuel ou non dans la liste des comptes du gestionnaire de comptabilité.
     * @param nom Nom du compte à ajouter.
     * @param nomParent Nom du compte parent dans la liste des comptes du gestionnaire de comptabilité pour le compte à ajouter.
     * @param virtuel Booléen indiquant si le compte doit être virtuel ou non.
     * @return Une référence vers le nouveau compte ajouté.
     */
    const CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel);
    /**
     * @brief Ajoute un compte avec un solde initial en dessous du compte racine du gestionnaire de comptabilité.
     * @param nom Nom du compte à ajouter.
     * @param classe Classe du compte à ajouter.
     * @param soldeInitial Solde initial du compte à ajouter.
     * @param dateSoldeInitial Date de la transaction du solde initial du compte à ajouter.
     * @param nomCompteCapitaux Nom du compte de capitaux pour l'initialisation du solde du compte à ajouter.
     * @return Une référence vers le nouveau compte ajouté.
     */
    const CompteAbstrait& ajouterCompte(const QString& nom, const ClasseCompte& classe, double soldeInitial, const QDate& dateSoldeInitial, const QString& nomCompteCapitaux);
    /**
     * @brief Ajoute un compte avec un solde initial avec parent à la liste des comptes du gestionnaire de comptabilité.
     * @param nom Nom du compte à ajouter.
     * @param nomParent Nom du compte parent du compte à ajouter.
     * @param soldeInitial Solde initial du compte à ajouter.
     * @param dateSoldeInitial Date de la transaction du solde initial du compte à ajouter.
     * @param nomCompteCapitaux Nom du compte de capitaux pour l'initialisation du solde du compte à ajouter.
     * @return Une référence vers le nouveau compte ajouté.
     */
    const CompteAbstrait& ajouterCompte(const QString& nom, const QString& nomParent, double soldeInitial, const QDate& dateSoldeInitial, const QString& nomCompteCapitaux);
    /**
     * @brief Ajoute un compte de capitaux à la listes des comptes du gestionnaire de comptabilité.
     * @param nom Nom du compte de capitaux.
     * @param nomParent Nom du compte parent du compte de capitaux.
     * @return Une référence vers le nouveau compte de capitaux ajouté.
     */
    const CompteAbstrait& ajouterCompteCapitaux(const QString& nom, const QString& nomParent);
    /**
     * @brief Ajoute une transaction à partir de sa data, sa référence, son intitulé et ses opérations dans la liste des transactions du gestionnaire de comptabilité.
     * @param date Date de la transaction.
     * @param reference Référence de la transaction.
     * @param intitule Intitulé de la transaction.
     * @param operations Opérations de la transaction.
     * @return Une référence vers la nouvelle transaction ajoutée.
     */
    const Transaction& ajouterTransaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations);
    /**
     * @brief Modifie une transaction de la liste des transactions du gestionnaire de comptabilité.
     * @param referenceTransaction Référence de la transaction à modifier.
     * @param nouvelleDate Nouvelle date de la transaction.
     * @param nouvelIntitule Nouvel intitulé de la transaction.
     * @param nouvellesOperations Nouvelles opérations de la transaction.
     * @return Une référence vers la transactions modifiée.
     */
    const Transaction& modifierTransaction(const QString& referenceTransaction, const QDate& nouvelleDate, const QString& nouvelIntitule, const QList<Operation>& nouvellesOperations);
    /**
     * @brief Supprime un compte de la liste des comptes du gestionnaire de comptabilité à partir de son nom.
     * @param nomCompte Nom du compte à supprimer.
     */
    void supprimerCompte(const QString& nomCompte);
    /**
     * @brief Supprime une transaction de la liste des transactions du gestionnaire de comptabilité à partir de sa référence.
     * @param referenceTransaction Référence de la transaction à supprimer.
     */
    void supprimerTransaction(const QString& referenceTransaction);
    /**
     * @brief Récupère le solde calculé d'un compte à partir d'une fonction de filtrage des transactions qui l'impliquent.
     * @param nomCompte Nom du compte dont on souhaite récupérer le solde calculé.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte.
     * @return Le solde calculé du compte à partir de la fonction de filtrage des transactions qui l'impliquent.
     */
    double getSoldeCalculeCompte(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions = [](const Transaction&) { return true; }) const;
    /**
     * @brief Récupère les soldes calculés d'un compte et de l'ensemble de ses enfants à partir d'une fonction de filtrage des transactions qui les impliquent.
     * @param nomCompte Nom du compte dont on souhaite récupérer le solde calculé et celui de l'ensemble de ses enfants.
     * @param filtreurTransactions Filtreur des transactions qui impliquent le compte et l'ensemble de ses enfants.
     * @return Les soldes calculés du compte et de l'ensemble de ses enfants sous forme d'une structure à partir de la fonction de filtrage des transactions qui les impliquent.
     */
    comptes_soldes_wrapper getSoldesCalculesCompteEtEnfants(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions = [](const Transaction&) { return true; }) const;
    /**
     * @brief Effectue la clôture du livret.
     */
    void effectuerCloture();
    /**
     * @brief Rapproche un compte de la liste des comptes du gestionnaire de comptabilité pour une date donnée.
     * @param nomCompte Nom du compte à rapprocher.
     * @param dateRapprochement Date à laquelle rapprocher le compte.
     */
    void rapprocherCompte(const QString& nomCompte, const QDate& dateRapprochement);
    /**
     * @brief Sauvegarde les données du gestionnaire de comptabilité dans un nouveau fichier
     * @param nomFichier Nom du nouveau fichier dans lequel sauvegarder les données du gestionnaire de comptabilité.
     */
    void sauvegarder(const QString& nomFichier);
    /**
     * @brief Sauvegarde les données du gestionnaire de comptabilité dans son fichier
     */
    void sauvegarder();

signals:
    /**
     * @brief Signal émis lorsqu'un compte est ajouté à la liste des comptes du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte ajouté.
     */
    void compteAjoute(const QString& nomCompte) const;
    /**
     * @brief Signal émis lorsqu'un compte est modifié dans la liste des comptes du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte modifié.
     */
    void compteModifie(const QString& nomCompte) const;
    /**
     * @brief Signal émis lorsqu'un compte est supprimé de la liste des comptes du gestionnaire de comptabilité.
     * @param nomCompte Nom du compte supprimé.
     */
    void compteSupprime(const QString& nomCompte) const;
    /**
     * @brief Signal émis lorsqu'une transaction est ajoutée à la liste des transactions du gestionnaire de comptabilité.
     * @param referenceTransaction Référence de la transaction ajoutée.
     */
    void transactionAjoutee(const QString& referenceTransaction) const;
    /**
     * @brief Signal émis lorsqu'une transaction est modifiée dans la liste des transactions du gestionnaire de comptabilité.
     * @param referenceTransaction Référence de la transaction modifiée.
     */
    void transactionModifiee(const QString& referenceTransaction) const;
    /**
     * @brief Signal émis lorsqu'une transaction est supprimée de la liste des transactions du gestionnaire de comptabilité.
     * @param referenceTransaction Référence de la transaction supprimée.
     */
    void transactionSupprimee(const QString& referenceTransaction) const;
};

#endif // COMPTABILITEMANAGER_H
