#include "CreationCompteDialog.h"
#include "ui_CreationCompteDialog.h"
#include "core/CompteException.h"
#include <QMessageBox>

CreationCompteDialog::CreationCompteDialog(QWidget *parent): QDialog(parent), ui(new Ui::CreationCompteDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    initialiserChoixComptes();
    updateChoixClasse();
    updateGroupeSoldeInitial();
}

CreationCompteDialog::~CreationCompteDialog() {
    delete ui;
}

void CreationCompteDialog::initialiserChoixComptes() {
    for(const CompteAbstrait& compte : manager.comptes()) {
        if(compte.getType() == VIRTUEL || compte.getType() == RACINE) {
            ui->choixCompteParent->addItem(compte.getNom());
        } else if(compte.getClasse() == PASSIF) {
            ui->choixCompteCapitaux->addItem(compte.getNom());
        }
    }
}

void CreationCompteDialog::on_boutonFermer_clicked() {
    close();
}

void CreationCompteDialog::updateGroupeSoldeInitial() {
    bool estVirtuel = ui->checkboxVirtuel->isChecked();
    ClasseCompte classe = getClasseCompte(ui->choixClasse->currentText());
    bool afficher = !estVirtuel && (classe == ACTIF || classe == PASSIF);
    ui->groupSoldeInitial->setEnabled(afficher);
}

void CreationCompteDialog::updateChoixClasse() {
    QString nomParent = ui->choixCompteParent->currentText();
    bool enfantRacine = manager.getCompteRacine().getNom() == nomParent;
    ui->labelClasse->setEnabled(enfantRacine);
    ui->choixClasse->setEnabled(enfantRacine);
}

void CreationCompteDialog::on_checkboxVirtuel_stateChanged(int) {
    updateGroupeSoldeInitial();
}

void CreationCompteDialog::on_choixCompteParent_currentIndexChanged(int) {
    updateChoixClasse();
}

void CreationCompteDialog::on_spinBoxMontant_valueChanged(double value) {
    bool activerChoixCapitaux = value > 0;
    ui->labelCompteCapitaux->setEnabled(activerChoixCapitaux);
    ui->choixCompteCapitaux->setEnabled(activerChoixCapitaux);
}

void CreationCompteDialog::on_boutonCreer_clicked() {
    try {
        QString nomCompte = ui->textNom->text();
        bool virtuel = ui->checkboxVirtuel->isChecked();
        if(ui->choixClasse->isEnabled()) {
            ClasseCompte classeCompte = getClasseCompte(ui->choixClasse->currentText());
            manager.ajouterCompte(nomCompte, classeCompte, virtuel);
        } else {
            QString nomParent = ui->choixCompteParent->currentText();
            manager.ajouterCompte(nomCompte, nomParent, virtuel);
        }
        close();
    } catch(const CompteException& e) {
        QMessageBox::critical(this, "Erreur de création", e.what());
    }
}

void CreationCompteDialog::on_choixClasse_currentIndexChanged(int) {
    updateGroupeSoldeInitial();
}
