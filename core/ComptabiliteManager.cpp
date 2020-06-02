#include "core/ComptabiliteManager.h"
#include "core/CompteException.h"
#include "core/SauvegardeException.h"
#include <QFile>
#include <QTextStream>

ComptabiliteManager::Handler ComptabiliteManager::handler = ComptabiliteManager::Handler();

ComptabiliteManager::ComptabiliteManager(const QString& filename): filename(filename), compteRacine(new CompteRacine()), mapComptes() {
    mapComptes.insert(compteRacine->getNom(), compteRacine);
    if(!filename.isNull()) {

    }
}

ComptabiliteManager::~ComptabiliteManager() {
    delete compteRacine;
}

ComptabiliteManager& ComptabiliteManager::charger(const QString& filename) {
    if(handler.instance)
        throw CompteException("ComptabiliteManager est déjà instancié !");
    handler.instance = new ComptabiliteManager(filename);
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

CompteAbstrait& ComptabiliteManager::getCompte(const QString& nom) const {
    CompteAbstrait* cpt = mapComptes.value(nom, nullptr);
    if(!cpt)
        throw CompteException("Compte " + nom + " inexistant !");
    return *cpt;
}

CompteAbstrait& ComptabiliteManager::ajouterCompte(const QString& nom, const ClasseCompte& classe, bool virtuel) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    CompteAbstrait* cpt;
    if(virtuel) {
        cpt = new CompteVirtuel(nom, classe, *compteRacine);
    } else {
        cpt = new Compte(nom, classe, *compteRacine);
    }
    mapComptes.insert(nom, cpt);
    emit comptesModifies();
    return *cpt;
}

CompteAbstrait& ComptabiliteManager::ajouterCompte(const QString& nom, const QString& nomParent, bool virtuel) {
    if(existeCompte(nom))
        throw CompteException("Nom de compte " + nom + " déjà utilisé !");
    CompteAbstrait& cptParent = getCompte(nomParent);
    CompteAbstrait* cpt;
    if(virtuel) {
        cpt = new CompteVirtuel(nom, cptParent);
    } else {
        cpt = new Compte(nom, cptParent);
    }
    mapComptes.insert(nom, cpt);
    emit comptesModifies();
    return *cpt;
}

void ComptabiliteManager::sauvegarder(const QString& filename) {
    if(filename.isNull() || filename.isEmpty())
        throw SauvegardeException("Fichier de sauvegarde non défini !");
    QFile outFile(filename);
    if(!outFile.open(QIODevice::ReadWrite))
        throw SauvegardeException("Erreur lors de la création du fichier " + filename + " !");
    QTextStream stream(&outFile);
    QDomDocument doc;
    stream << doc.toString();
    outFile.close();
    this->filename = filename;
}

void ComptabiliteManager::sauvegarder() {
    sauvegarder(filename);
}
