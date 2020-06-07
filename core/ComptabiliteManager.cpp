#include "core/ComptabiliteManager.h"
#include "core/CompteException.h"
#include "core/SauvegardeException.h"
#include "core/TransactionException.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
            QDomDocument doc;
            doc.setContent(&file);
            chargerComptes(doc);
            chargerTransactions(doc);
        } catch(const exception& e) {
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
        QString nom = compteXml.attribute("nom").toUtf8();
        QString nomParent = compteXml.attribute("parent").toUtf8();
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
        QString reference = transactionXml.attribute("reference").toUtf8();
        QString intitule = transactionXml.attribute("intitule").toUtf8();
        QList<Operation> operations;
        QDomNodeList operationsXml = transactionXml.elementsByTagName("Operation");
        for(int j = 0; j < operationsXml.size(); ++j) {
            QDomElement operationXml = operationsXml.item(j).toElement();
            double montant = operationXml.attribute("montant").toDouble();
            TypeOperation type = static_cast<TypeOperation>(operationXml.attribute("type").toUInt());
            QString nomCompte = operationXml.attribute("compte").toUtf8();
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
    for(const Transaction* transaction : mapTransactions) {
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
    mapComptes.insert(compte->getNom(), compte);
    emit compteAjoute(compte->getNom());
    sauvegarde = false;
}

CompteAbstrait& ComptabiliteManager::getCompteParNom(const QString& nom) const {
    CompteAbstrait* cpt = mapComptes.value(nom, nullptr);
    if(!cpt)
        throw CompteException("Compte " + nom + " inexistant !");
    return *cpt;
}

ComptabiliteManager::comptes_iterator_proxy ComptabiliteManager::getComptesVirtuels() const {
    QList<CompteAbstrait*> comptesVirtuels;
    for(CompteAbstrait* compte : mapComptes) {
        if(compte->getType() == VIRTUEL) {
            comptesVirtuels.append(compte);
        }
    }
    return comptesVirtuels;
}

ComptabiliteManager::comptes_iterator_proxy ComptabiliteManager::getComptesSimples() const {
    QList<CompteAbstrait*> comptesSimples;
    for(CompteAbstrait* compte : mapComptes) {
        if(compte->getType() == SIMPLE) {
            comptesSimples.append(compte);
        }
    }
    return comptesSimples;
}

void ComptabiliteManager::ajouterTransaction(Transaction* transaction) {
    mapTransactions.insert(transaction->getReference(), transaction);
    emit transactionAjoutee(transaction->getReference());
    sauvegarde = false;
}

Transaction& ComptabiliteManager::getTransactionParReference(const QString& reference) const {
    Transaction* transac = mapTransactions.value(reference, nullptr);
    if(!transac)
        throw TransactionException("Transaction " + reference + " inexistante !");
    return *transac;
}

void ComptabiliteManager::verifierOperations(const QList<Operation>& operations) const {
    for(const Operation& operation : operations) {
        if(!existeCompte(operation.getNomCompte()))
            throw TransactionException("Le compte " + operation.getNomCompte() + " de la transaction n'existe pas !");
    }
}

void ComptabiliteManager::appliquerTransaction(const Transaction* transaction) {
    for(const Operation& operation : transaction->operations()) {
        double montant = operation.getMontant();
        const TypeOperation& type = operation.getType();
        CompteAbstrait& compte = getCompteParNom(operation.getNomCompte());
        if(type == DEBIT) {
            compte.debiter(montant);
        } else {
            compte.crediter(montant);
        }
    }
}

void ComptabiliteManager::informerModificationComptes(const Transaction* transaction) const {
    for(const Operation& operation : transaction->operations()) {
        emit compteModifie(operation.getNomCompte());
    }
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

bool transactionsLesserCompare(const Transaction* t1, const Transaction* t2) {
    return t1->getDate() < t2->getDate();
}

ComptabiliteManager::transactions_iterator_proxy ComptabiliteManager::transactions() const {
    QList<Transaction*> transactions = mapTransactions.values();
    std::stable_sort(transactions.begin(), transactions.end(), transactionsLesserCompare);
    return transactions;
}

ComptabiliteManager::transactions_iterator_proxy ComptabiliteManager::getTransactionsCompte(const QString& nom) const {
    QList<Transaction*> transactions;
    for(Transaction* transaction : mapTransactions) {
        if(transaction->impliqueCompte(nom)) {
            transactions.append(transaction);
        }
    }
    std::stable_sort(transactions.begin(), transactions.end(), transactionsLesserCompare);
    return transactions;
}

const Transaction& ComptabiliteManager::ajouterTransaction(const QDate& date, const QString& reference, const QString& intitule, const QList<Operation>& operations) {
    if(existeTransaction(reference))
        throw CompteException("Référence de transaction " + reference + " déjà utilisé !");
    verifierOperations(operations);
    Transaction* transaction = new Transaction(date, reference, intitule, operations);
    appliquerTransaction(transaction);
    ajouterTransaction(transaction);
    informerModificationComptes(transaction);
    return *transaction;
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
