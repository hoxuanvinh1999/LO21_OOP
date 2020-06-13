#include "core/ComptabiliteManager.h"
#include "core/CompteException.h"
#include "core/SauvegardeException.h"
#include "core/TransactionException.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

ComptabiliteManager::Handler ComptabiliteManager::handler = ComptabiliteManager::Handler();

ComptabiliteManager::ComptabiliteManager(const QString& nomFichier): nomFichier(nomFichier)  {
    ajouterCompte(&compteRacine);
    chargerDonnees();
    sauvegarde = true;
}

void ComptabiliteManager::chargerDonnees() {
    if(!nomFichier.isNull()) {
        QFile fichier(nomFichier);
        if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
            throw SauvegardeException("Erreur de lecture du fichier de sauvegarde !");
        try {
            QTextStream in(&fichier);
            in.setCodec(QTextCodec::codecForName("ISO 8859-1"));
            QString content = in.readAll();
            QDomDocument doc;
            doc.setContent(content);
            chargerComptes(doc);
            chargerTransactions(doc);
            fichier.close();
        } catch(const exception& e) {
            fichier.close();
            throw SauvegardeException("Fichier de sauvegarde corrompu !");
        }
    }
}

void ComptabiliteManager::chargerComptes(const QDomDocument& doc) {
    QDomNodeList comptesXml = doc.elementsByTagName("Compte");
    if(comptesXml.size() == 0 || static_cast<TypeCompte>(comptesXml.item(0).toElement().attribute("type").toUInt()) != RACINE)
        throw SauvegardeException("Fichier de sauvegarde corrompu !");
    for(int i = 1; i < comptesXml.size(); ++i) {
        QDomElement compteXml = comptesXml.item(i).toElement();
        TypeCompte type = static_cast<TypeCompte>(compteXml.attribute("type").toUInt());
        bool virtuel = type == VIRTUEL;
        QString nom = compteXml.attribute("nom");
        QString nomParent = compteXml.attribute("parent");
        if(nomParent == compteRacine.getNom()) {
            ClasseCompte classe = static_cast<ClasseCompte>(compteXml.attribute("classe").toUInt());
            ajouterCompte(nom, classe, virtuel);
        } else {
            ajouterCompte(nom, nomParent, virtuel);
        }
    }
}

void ComptabiliteManager::chargerTransactions(const QDomDocument& doc) {
    QDomNodeList transactionsXml = doc.elementsByTagName("Transaction");
    for(int i = 0; i < transactionsXml.size(); ++i) {
        QDomElement transactionXml = transactionsXml.item(i).toElement();
        QDate date = QDate::fromString(transactionXml.attribute("date"), Qt::LocalDate);
        QString reference = transactionXml.attribute("reference");
        QString intitule = transactionXml.attribute("intitule");
        QList<Operation> operations;
        QDomNodeList operationsXml = transactionXml.elementsByTagName("Operation");
        for(int j = 0; j < operationsXml.size(); ++j) {
            QDomElement operationXml = operationsXml.item(j).toElement();
            double montant = operationXml.attribute("montant").toDouble();
            TypeOperation type = static_cast<TypeOperation>(operationXml.attribute("type").toUInt());
            QString nomCompte = operationXml.attribute("compte");
            operations.append(Operation(montant, type, nomCompte));
        }
        ajouterTransaction(date, reference, intitule, operations);
    }
}

void ComptabiliteManager::sauvegarderComptes(QDomDocument& doc, QDomElement& racineDoc) const {
    QDomElement comptesXml = doc.createElement("Comptes");
    racineDoc.appendChild(comptesXml);
    sauvegarderCompteEtEnfants(doc, comptesXml, compteRacine);
}

void ComptabiliteManager::sauvegarderCompteEtEnfants(QDomDocument& doc, QDomElement& comptesXml, const CompteAbstrait& compte) const {
    QDomElement compteXml = compte.serialiser(doc);
    comptesXml.appendChild(compteXml);
    for(const CompteAbstrait& compteEnfant : compte) {
        sauvegarderCompteEtEnfants(doc, comptesXml, compteEnfant);
    }
}

void ComptabiliteManager::sauvegarderTransactions(QDomDocument& doc, QDomElement& racineDoc) const {
    QDomElement transactionsXml = doc.createElement("Transactions");
    racineDoc.appendChild(transactionsXml);
    for(const Transaction* transaction : transactions) {
        QDomElement transactionXml = transaction->serialiser(doc);
        transactionsXml.appendChild(transactionXml);
    }
}

void ComptabiliteManager::ajouterCompte(CompteAbstrait* compte) {
    comptes.append(compte);
    emit compteAjoute(compte->getNom());
    sauvegarde = false;
}

void ComptabiliteManager::supprimerCompte(CompteAbstrait* compte) {
    if(compte->getType() == SIMPLE) {
        for(Transaction* transaction : transactions) {
            if(transaction->impliqueCompte(compte->getNom()))
                supprimerTransaction(transaction);
        }
    } else {
        for(CompteAbstrait& compteEnfant : *compte) {
            supprimerCompte(&compteEnfant);
        }
    }
    comptes.removeAt(comptes.indexOf(compte));
    QString nomCompte = compte->getNom();
    delete compte;
    emit compteSupprime(nomCompte);
    sauvegarde = false;
}

CompteAbstrait& ComptabiliteManager::getCompteParNom(const QString& nomCompte) {
    for(CompteAbstrait* compte : comptes) {
        if(compte->getNom() == nomCompte)
            return *compte;
    }
    throw CompteException("Compte " + nomCompte + " inexistant !");
}

const CompteAbstrait& ComptabiliteManager::getCompteParNom(const QString& nomCompte) const {
    for(const CompteAbstrait* compte : comptes) {
        if(compte->getNom() == nomCompte)
            return *compte;
    }
    throw CompteException("Compte " + nomCompte + " inexistant !");
}

QSet<QString> ComptabiliteManager::getNomCompteEtEnfants(const CompteAbstrait* compte) const {
    QSet<QString> nomComptes;
    nomComptes.insert(compte->getNom());
    for(const CompteAbstrait& compteEnfant : *compte) {
        nomComptes.unite(getNomCompteEtEnfants(&compteEnfant));
    }
    return nomComptes;
}

bool ComptabiliteManager::compteEstSupprimable(const CompteAbstrait* compte) const {
    if(compte->getNom() == compteRacine.getNom())
        return false;
    for(const Transaction& transactionCompte : getTransactionsCompte(compte->getNom())) {
        if(transactionCompte.estFigee())
            return false;
    }
    for(const CompteAbstrait& compteEnfant : *compte) {
        if(!compteEstSupprimable(&compteEnfant))
            return false;
    }
    return true;
}

void ComptabiliteManager::verifierOperations(const QList<Operation>& operations) const {
    for(const Operation& operation : operations) {
        if(!existeCompte(operation.getNomCompte()))
            throw TransactionException("Le compte " + operation.getNomCompte() + " de la transaction n'existe pas !");
    }
}

void ComptabiliteManager::informerModificationCompte(const CompteAbstrait* compte) const {
    if(compte) {
        emit compteModifie(compte->getNom());
        informerModificationCompte(compte->getParent());
    }
}

void ComptabiliteManager::appliquerTransaction(const Transaction* transaction) {
    for(const Operation& operation : *transaction) {
        double montant = operation.getMontant();
        const TypeOperation& type = operation.getType();
        CompteAbstrait& compte = getCompteParNom(operation.getNomCompte());
        if(type == DEBIT) {
            compte.debiter(montant);
        } else {
            compte.crediter(montant);
        }
        informerModificationCompte(&compte);
    }
}

void ComptabiliteManager::annulerTransaction(const Transaction* transaction) {
    for(const Operation& operation : *transaction) {
        double montant = operation.getMontant();
        const TypeOperation& type = operation.getType();
        CompteAbstrait& compte = getCompteParNom(operation.getNomCompte());
        if(type == DEBIT) {
            compte.crediter(montant);
        } else {
            compte.debiter(montant);
        }
        informerModificationCompte(&compte);
    }
}

void ComptabiliteManager::ajouterTransaction(Transaction* transaction) {
    transactions.append(transaction);
    emit transactionAjoutee(transaction->getReference());
    appliquerTransaction(transaction);
    sauvegarde = false;
}

void ComptabiliteManager::supprimerTransaction(Transaction* transaction) {
    transactions.removeAt(transactions.indexOf(transaction));
    annulerTransaction(transaction);
    QString referenceTransaction = transaction->getReference();
    delete transaction;
    emit transactionSupprimee(referenceTransaction);
    sauvegarde = false;
}

Transaction& ComptabiliteManager::getTransactionParReference(const QString& referenceTransaction) {
    for(Transaction* transaction : transactions) {
        if(transaction->getReference() == referenceTransaction)
            return *transaction;
    }
    throw TransactionException("Transaction " + referenceTransaction + " inexistante !");
}

const Transaction& ComptabiliteManager::getTransactionParReference(const QString& referenceTransaction) const {
    for(const Transaction* transaction : transactions) {
        if(transaction->getReference() == referenceTransaction)
            return *transaction;
    }
    throw TransactionException("Transaction " + referenceTransaction + " inexistante !");
}

double ComptabiliteManager::getSoldeCalculeCompte(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions) const {
    double solde = 0;
    if(compte.getType() == SIMPLE) {
        for(const Transaction& transaction : getTransactionsCompte(compte.getNom())) {
            if(filtreurTransactions(transaction)) {
                const Operation& operation = transaction.getOperation(compte.getNom());
                if(operation.getType() == DEBIT) {
                    solde += operation.getMontant();
                } else {
                    solde -= operation.getMontant();
                }
            }
        }
        if(compte.getClasse() == PASSIF || compte.getClasse() == RECETTE) solde *= -1;
    } else {
        for(const CompteAbstrait& compteEnfant : compte) {
            solde += getSoldeCalculeCompte(compteEnfant, filtreurTransactions);
        }
    }
    return solde;
}

QList<CompteSoldeStruct> ComptabiliteManager::getSoldesCalculesCompteEtEnfants(const CompteAbstrait& compte, const function<bool(const Transaction&)>& filtreurTransactions) const {
    QList<CompteSoldeStruct> soldesComptes;
    double soldeCompte = 0;
    if(compte.getType() == SIMPLE) {
        soldeCompte = getSoldeCalculeCompte(compte, filtreurTransactions);
    } else {
        for(const CompteAbstrait& compteEnfant : compte) {
            QList<CompteSoldeStruct> soldesComptesEnfants = getSoldesCalculesCompteEtEnfants(compteEnfant, filtreurTransactions);
            soldeCompte += soldesComptesEnfants.first().solde;
            soldesComptes.append(soldesComptesEnfants);
        }
    }
    soldesComptes.push_front({compte.getNom(), soldeCompte});
    return soldesComptes;
}

ComptabiliteManager& ComptabiliteManager::charger(const QString& nomFichier) {
    if(handler.instance)
        throw CompteException("ComptabiliteManager est déjà instancié !");
    handler.instance = new ComptabiliteManager(nomFichier);
    return *handler.instance;
}

ComptabiliteManager& ComptabiliteManager::getInstance() {
    if(!handler.instance)
        throw CompteException("ComptabiliteManager n'est pas encore instancié !");
    return *handler.instance;
}

void ComptabiliteManager::libererInstance() {
    delete handler.instance;
    handler.instance = nullptr;
}

bool ComptabiliteManager::estInstancie() {
    return handler.instance;
}

bool ComptabiliteManager::existeCompte(const QString& nomCompte) const {
    for(const CompteAbstrait* compte : comptes) {
        if(compte->getNom() == nomCompte)
            return true;
    }
    return false;
}

QSet<QString> ComptabiliteManager::getNomCompteEtEnfants(const QString& nomCompte) const {
    const CompteAbstrait& compte = getCompteParNom(nomCompte);
    return getNomCompteEtEnfants(&compte);
}

ComptabiliteManager::comptes_iterator_proxy ComptabiliteManager::getComptes(const function<bool(const CompteAbstrait&)>& filtreurComptes) const {
    QList<CompteAbstrait*> comptes;
    for(CompteAbstrait* compte : this->comptes) {
        if(filtreurComptes(*compte)) {
            comptes.append(compte);
        }
    }
    return comptes;
}

bool ComptabiliteManager::compteEstSupprimable(const QString& nomCompte) const {
    const CompteAbstrait& compte = getCompteParNom(nomCompte);
    return compteEstSupprimable(&compte);
}

bool ComptabiliteManager::existeTransaction(const QString& referenceTransaction) const {
    for(const Transaction* transaction : transactions) {
        if(transaction->getReference() == referenceTransaction)
            return true;
    }
    return false;
}

ComptabiliteManager::transactions_iterator_proxy ComptabiliteManager::getTransactions(const function<bool(const Transaction&)>& filtreurTransactions) const {
    QList<Transaction*> transactions;
    for(Transaction* transaction : this->transactions) {
        if(filtreurTransactions(*transaction)){
            transactions.append(transaction);
        }
    }
    return transactions;
}

ComptabiliteManager::transactions_iterator_proxy ComptabiliteManager::getTransactionsCompte(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions) const {
    const CompteAbstrait& compte = getCompteParNom(nomCompte);
    QList<Transaction*> transactionsCompte;
    for(Transaction* transaction : this->transactions) {
        if(transaction->impliqueCompte(compte.getNom()) && filtreurTransactions(*transaction)) {
            transactionsCompte.append(transaction);
        }
    }
    return transactionsCompte;
}

const CompteAbstrait& ComptabiliteManager::ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    CompteAbstrait* compte;
    if(virtuel) {
        compte = new CompteVirtuel(nom, classe, &compteRacine);
    } else {
        compte = new Compte(nom, classe, &compteRacine);
    }
    ajouterCompte(compte);
    return *compte;
}

const CompteAbstrait& ComptabiliteManager::ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    CompteAbstrait& cptParent = getCompteParNom(nomParent);
    CompteAbstrait* compte;
    if(virtuel) {
        compte = new CompteVirtuel(nom, &cptParent);
    } else {
        compte = new Compte(nom, &cptParent);
    }
    ajouterCompte(compte);
    return *compte;
}

const CompteAbstrait& ComptabiliteManager::ajouterCompte(const QString& nom, const ClasseCompte& classe, double soldeInitial, const QString& nomCompteCapitaux) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    if(classe != ACTIF && classe != PASSIF)
        throw CompteException("Un compte avec un solde initial doit être un compte de passifs et d'actifs !");
    CompteAbstrait& compteCapitaux = getCompteParNom(nomCompteCapitaux);
    if(compteCapitaux.getType() != SIMPLE || compteCapitaux.getClasse() != PASSIF)
        throw CompteException("Un compte de capitaux doit être un compte de passifs !");
    CompteAbstrait* compte = new Compte(nom, classe, &compteRacine);
    ajouterCompte(compte);
    int i = 1;
    while(existeTransaction("I" + QString::number(i))) { ++i; }
    QList<Operation> operations;
    if(classe == ACTIF) {
        operations.append(Operation(soldeInitial, DEBIT, nom));
        operations.append(Operation(soldeInitial, CREDIT, nomCompteCapitaux));
    } else {
        operations.append(Operation(soldeInitial, CREDIT, nom));
        operations.append(Operation(soldeInitial, DEBIT, nomCompteCapitaux));
    }
    Transaction* transaction = new Transaction(QDate::currentDate(), "I" + QString::number(i), "Solde initial", operations);
    ajouterTransaction(transaction);
    return *compte;
}

const CompteAbstrait& ComptabiliteManager::ajouterCompte(const QString& nom, const QString& nomParent, double soldeInitial, const QString& nomCompteCapitaux) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    CompteAbstrait& compteParent = getCompteParNom(nomParent);
    if(compteParent.getClasse() != ACTIF && compteParent.getClasse() != PASSIF)
        throw CompteException("Un compte avec un solde initial doit être un compte de passifs et d'actifs !");
    CompteAbstrait& compteCapitaux = getCompteParNom(nomCompteCapitaux);
    if(compteCapitaux.getType() != SIMPLE || compteCapitaux.getClasse() != PASSIF)
        throw CompteException("Un compte de capitaux doit être un compte de passifs !");
    CompteAbstrait* compte = new Compte(nom, &compteParent);
    ajouterCompte(compte);
    int i = 1;
    while(existeTransaction("I" + QString::number(i))) { ++i; }
    QList<Operation> operations;
    if(compte->getClasse() == ACTIF) {
        operations.append(Operation(soldeInitial, DEBIT, nom));
        operations.append(Operation(soldeInitial, CREDIT, nomCompteCapitaux));
    } else {
        operations.append(Operation(soldeInitial, CREDIT, nom));
        operations.append(Operation(soldeInitial, DEBIT, nomCompteCapitaux));
    }
    Transaction* transaction = new Transaction(QDate::currentDate(), "I" + QString::number(i), "Solde initial", operations);
    ajouterTransaction(transaction);
    return *compte;
}

const CompteAbstrait& ComptabiliteManager::ajouterCompteCapitaux(const QString& nom, const QString& nomParent) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    Compte* compte;
    if(nomParent == compteRacine.getNom()) {
        compte = new Compte(nom, PASSIF, &compteRacine);
    } else {
        CompteAbstrait& cptParent = getCompteParNom(nomParent);
        if(cptParent.getClasse() != PASSIF)
            throw CompteException("Un compte de capitaux doit être un compte de passifs !");
        compte = new Compte(nom, &cptParent);
    }
    ajouterCompte(compte);
    return *compte;
}

const Transaction& ComptabiliteManager::ajouterTransaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations) {
    if(existeTransaction(reference))
        throw TransactionException("Référence de transaction " + reference + " déjà utilisé !");
    verifierOperations(operations);
    Transaction* transaction = new Transaction(date, reference, intitule, operations);
    ajouterTransaction(transaction);
    return *transaction;
}

const Transaction& ComptabiliteManager::modifierTransaction(const QString& referenceTransaction, const QDate& nouvelleDate, const QString& nouvelIntitule, const QList<Operation>& nouvellesOperations) {
    Transaction& transaction = getTransactionParReference(referenceTransaction);
    if(transaction.estFigee())
        throw TransactionException("Une transaction figée ne peut pas être modifiée !");
    annulerTransaction(&transaction);
    try {
        transaction.modifier(nouvelleDate, nouvelIntitule, nouvellesOperations);
    } catch (const TransactionException& e) {
        appliquerTransaction(&transaction);
        throw e;
    }
    appliquerTransaction(&transaction);
    emit transactionModifiee(transaction.getReference());
    sauvegarde = false;
    return transaction;
}

void ComptabiliteManager::supprimerCompte(const QString& nomCompte) {
    CompteAbstrait& compte = getCompteParNom(nomCompte);
    if(!compteEstSupprimable(&compte))
        throw CompteException("Un compte avec des transactions figées n'est pas supprimable !");
    supprimerCompte(&compte);
}

void ComptabiliteManager::supprimerTransaction(const QString& referenceTransaction) {
    Transaction& transaction = getTransactionParReference(referenceTransaction);
    if(transaction.estFigee())
        throw TransactionException("Une transaction figée ne peut pas être supprimée !");
    supprimerTransaction(&transaction);
}

double ComptabiliteManager::getSoldeCalculeCompte(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions) const {
    const CompteAbstrait& compte = getCompteParNom(nomCompte);
    return getSoldeCalculeCompte(compte, filtreurTransactions);
}

QList<CompteSoldeStruct> ComptabiliteManager::getSoldesCalculesCompteEtEnfants(const QString& nomCompte, const function<bool(const Transaction&)>& filtreurTransactions) const {
    const CompteAbstrait& compte = getCompte(nomCompte);
    return getSoldesCalculesCompteEtEnfants(compte, filtreurTransactions);
}

void ComptabiliteManager::effectuerCloture() {
    if(!existeCompte("Résultat")) {
        ajouterCompte("Résultat", PASSIF, false);
    }
    if(!existeCompte("Excédent")) {
        ajouterCompte("Excédent", PASSIF, false);
    }
    if(!existeCompte("Déficit")) {
        ajouterCompte("Déficit", PASSIF, false);
    }
    double soldeDepenses = 0;
    double soldeRecettes = 0;
    QList<Operation> operationsDepenses;
    QList<Operation> operationsRecettes;
    for(const CompteAbstrait* compte : comptes) {
        if(compte->getType() == SIMPLE && (compte->getClasse() == DEPENSE || compte->getClasse() == RECETTE)) {
            double soldeCompte = compte->getSolde();
            if(soldeCompte != 0) {
                if(compte->getClasse() == DEPENSE) {
                    soldeDepenses += soldeCompte;
                    if(soldeCompte > 0) {
                        operationsDepenses.append(Operation(soldeCompte, CREDIT, compte->getNom()));
                    } else {
                        operationsDepenses.append(Operation(-soldeCompte, DEBIT, compte->getNom()));
                    }
                } else if(compte->getClasse() == RECETTE) {
                    soldeRecettes += soldeCompte;
                    if(soldeCompte > 0) {
                        operationsRecettes.append(Operation(soldeCompte, DEBIT, compte->getNom()));
                    } else {
                        operationsRecettes.append(Operation(soldeCompte, CREDIT, compte->getNom()));
                    }
                }
            }
        }
    }
    if(operationsDepenses.size() + operationsRecettes.size() == 0)
        throw TransactionException("Aucune opérations et transactions nécessaires pour la clôture !");
    int i = 1;
    while(existeTransaction("CL" + QString::number(i) + "D") && existeTransaction("CL" + QString::number(i) + "R")) ++i;
    if(operationsDepenses.size() > 0) {
        if(soldeDepenses >= 0) {
            operationsDepenses.append(Operation(soldeDepenses, DEBIT, "Résultat"));
        } else {
            operationsDepenses.append(Operation(soldeDepenses, CREDIT, "Résultat"));
        }
        ajouterTransaction(QDate::currentDate(), "CL" + QString::number(i) + "D", "Clôture " + QString::number(i) + " - dépenses", operationsDepenses);
    }
    if(operationsRecettes.size() > 0) {
        if(soldeRecettes >= 0) {
            operationsRecettes.append(Operation(soldeRecettes, CREDIT, "Résultat"));
        } else {
            operationsRecettes.append(Operation(soldeRecettes, DEBIT, "Résultat"));
        }
        ajouterTransaction(QDate::currentDate(), "CL" + QString::number(i) + "R", "Clôture " + QString::number(i) + " - recettes", operationsRecettes);
    }
    const CompteAbstrait& compteResultat = getCompteParNom("Résultat");
    double soldeResultat = compteResultat.getSolde();
    if(soldeResultat > 0) {
        QList<Operation> operationsBenefices;
        operationsBenefices.append(Operation(soldeResultat, DEBIT, "Résultat"));
        operationsBenefices.append(Operation(soldeResultat, CREDIT, "Excédent"));
        ajouterTransaction(QDate::currentDate(), "AFF" + QString::number(i), "Clôture " + QString::number(i) + " - affectation bénéfice", operationsBenefices);
    } else if(soldeResultat < 0) {
        soldeResultat *= -1;
        QList<Operation> operationsDeficit;
        operationsDeficit.append(Operation(soldeResultat, CREDIT, "Résultat"));
        operationsDeficit.append(Operation(soldeResultat, DEBIT, "Déficit"));
        ajouterTransaction(QDate::currentDate(), "AFF" + QString::number(i), "Clôture " + QString::number(i) + " - affectation perte", operationsDeficit);
    }
}

void ComptabiliteManager::sauvegarder(const QString& nomFichier) {
    QString ancienNomFichier = this->nomFichier;
    this->nomFichier = nomFichier;
    try {
        sauvegarder();
    } catch(const exception e) {
        this->nomFichier = ancienNomFichier;
        throw e;
    }
}

void ComptabiliteManager::sauvegarder() {
    if(nomFichier.isNull() || nomFichier.isEmpty())
        throw SauvegardeException("Fichier de sauvegarde non défini !");
    QFile fichier(nomFichier);
    if(!fichier.open(QIODevice::WriteOnly))
        throw SauvegardeException("Erreur lors de la création du fichier " + nomFichier + " !");
    QDomDocument doc("Comptabilite");
    QDomElement racineDoc = doc.createElement("Comptabilite");
    doc.appendChild(racineDoc);
    sauvegarderComptes(doc, racineDoc);
    sauvegarderTransactions(doc, racineDoc);
    QTextStream stream(&fichier);
    stream << doc.toString();
    fichier.close();
    sauvegarde = true;
}
