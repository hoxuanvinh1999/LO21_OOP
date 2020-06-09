#include "core/ComptabiliteManager.h"
#include "core/CompteException.h"
#include "core/SauvegardeException.h"
#include "core/TransactionException.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

ComptabiliteManager::Handler ComptabiliteManager::handler = ComptabiliteManager::Handler();

ComptabiliteManager::ComptabiliteManager(const QString& nomFichier): nomFichier(nomFichier), compteRacine(), mapComptes() {
    ajouterCompte(&compteRacine);
    chargerDonnees();
    sauvegarde = true;
}

void ComptabiliteManager::chargerDonnees() {
    if(!nomFichier.isNull()) {
        QFile file(nomFichier);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw SauvegardeException("Erreur de lecture du fichier de sauvegarde !");
        try {
            QTextStream in(&file);
            in.setCodec(QTextCodec::codecForName("ISO 8859-1"));
            QString content = in.readAll();
            QDomDocument doc;
            doc.setContent(content);
            chargerComptes(doc);
            chargerTransactions(doc);
            file.close();
        } catch(const exception& e) {
           file.close();
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

void ComptabiliteManager::ajouterCompte(CompteAbstrait* compte) {
    unsigned int index = comptes.size();
    comptes.append(compte);
    mapComptes.insert(compte->getNom(), index);
    emit compteAjoute(compte->getNom());
    sauvegarde = false;
}

CompteAbstrait& ComptabiliteManager::getCompteParNom(const QString& nom) const {
    int index = mapComptes.value(nom, -1);
    if(index == -1)
        throw CompteException("Compte " + nom + " inexistant !");
    return *comptes[index];
}

void ComptabiliteManager::informerModificationCompte(const CompteAbstrait* compte) const {
    if(compte) {
        emit compteModifie(compte->getNom());
        informerModificationCompte(compte->getParent());
    }
}

ComptabiliteManager::comptes_iterator_proxy ComptabiliteManager::getComptesVirtuels() const {
    QList<CompteAbstrait*> comptesVirtuels;
    for(CompteAbstrait* compte : comptes) {
        if(compte->getType() == VIRTUEL) {
            comptesVirtuels.append(compte);
        }
    }
    return comptesVirtuels;
}

ComptabiliteManager::comptes_iterator_proxy ComptabiliteManager::getComptesSimples() const {
    QList<CompteAbstrait*> comptesSimples;
    for(CompteAbstrait* compte : comptes) {
        if(compte->getType() == SIMPLE) {
            comptesSimples.append(compte);
        }
    }
    return comptesSimples;
}

void ComptabiliteManager::ajouterTransaction(Transaction* transaction) {
    unsigned int index = transactions.size();
    transactions.append(transaction);
    mapTransactions.insert(transaction->getReference(), index);
    emit transactionAjoutee(transaction->getReference());
    appliquerTransaction(transaction);
    sauvegarde = false;
}

void ComptabiliteManager::supprimerTransaction(Transaction* transaction) {
    transactions.removeAt(mapTransactions.value(transaction->getReference()));
    mapTransactions.remove(transaction->getReference());
    emit transactionSupprimee(transaction->getReference());
    annulerTransaction(transaction);
    delete transaction;
    sauvegarde = false;
}

Transaction& ComptabiliteManager::getTransactionParReference(const QString& reference) const {
    int index = mapTransactions.value(reference, -1);
    if(index == -1)
        throw TransactionException("Transaction " + reference + " inexistante !");
    return *transactions[index];
}

void ComptabiliteManager::verifierOperations(const QList<Operation>& operations) const {
    for(const Operation& operation : operations) {
        if(!existeCompte(operation.getNomCompte()))
            throw TransactionException("Le compte " + operation.getNomCompte() + " de la transaction n'existe pas !");
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
    }
}

QSet<QString> ComptabiliteManager::getNomCompteEtEnfants(const CompteAbstrait* compte) const {
    QSet<QString> nomComptes;
    nomComptes.insert(compte->getNom());
    for(const CompteAbstrait& compteEnfant : *compte) {
        nomComptes.unite(getNomCompteEtEnfants(&compteEnfant));
    }
    return nomComptes;
}

QSet<QString> ComptabiliteManager::getNomCompteEtEnfants(const QString& nomCompte) const {
    CompteAbstrait& compte = getCompteParNom(nomCompte);
    return getNomCompteEtEnfants(&compte);
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

ComptabiliteManager::transactions_iterator_proxy ComptabiliteManager::getTransactionsCompte(const QString& nom) const {
    CompteAbstrait& compte = getCompteParNom(nom);
    QList<Transaction*> transactionsCompte;
    for(Transaction* transaction : transactions) {
        if(transaction->impliqueCompte(compte.getNom())) {
            transactionsCompte.append(transaction);
        }
    }
    return transactionsCompte;
}

const Transaction& ComptabiliteManager::ajouterTransaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations) {
    if(existeTransaction(reference))
        throw TransactionException("Référence de transaction " + reference + " déjà utilisé !");
    verifierOperations(operations);
    Transaction* transaction = new Transaction(date, reference, intitule, operations);
    ajouterTransaction(transaction);
    return *transaction;
}

void ComptabiliteManager::supprimerTransaction(const QString& referenceTransaction) {
    if(!existeTransaction(referenceTransaction))
        throw TransactionException("La transaction de référence " + referenceTransaction + " n'existe pas !");
    Transaction& transaction = getTransactionParReference(referenceTransaction);
    if(transaction.estFigee())
        throw TransactionException("Une transaction figée ne peut pas être supprimée !");
    supprimerTransaction(&transaction);
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
    QFile outFile(nomFichier);
    if(!outFile.open(QIODevice::WriteOnly))
        throw SauvegardeException("Erreur lors de la création du fichier " + nomFichier + " !");
    QDomDocument doc("Comptabilite");
    QDomElement racineDoc = doc.createElement("Comptabilite");
    doc.appendChild(racineDoc);
    sauvegarderComptes(doc, racineDoc);
    sauvegarderTransactions(doc, racineDoc);
    QTextStream stream(&outFile);
    stream << doc.toString();
    outFile.close();
    sauvegarde = true;
}
