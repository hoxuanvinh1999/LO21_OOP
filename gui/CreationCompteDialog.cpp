#include "CreationCompteDialog.h"
#include "ui_CreationCompteDialog.h"
#include "core/CompteException.h"
#include "CreationCompteCapitauxDialog.h"
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
    for(const CompteAbstrait& compte : manager.getComptes()) {
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
    bool afficher;
    if(ui->choixClasse->isEnabled()) {
         afficher = !estVirtuel && (classe == ACTIF || classe == PASSIF);
    } else {
        const CompteAbstrait& compteParent = manager.getCompte(ui->choixCompteParent->currentText());
        afficher = !estVirtuel && (compteParent.getClasse() == ACTIF || compteParent.getClasse() == PASSIF);
    }
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
    updateGroupeSoldeInitial();
}

void CreationCompteDialog::on_spinBoxMontant_valueChanged(double value) {
    bool activerChoixCapitaux = value > 0;
    ui->labelCompteCapitaux->setEnabled(activerChoixCapitaux);
    ui->choixCompteCapitaux->setEnabled(activerChoixCapitaux);
}

void CreationCompteDialog::on_boutonCreer_clicked() {
    try {
        QString nomCompte = ui->textNom->text();
        if(ui->groupSoldeInitial->isChecked() && ui->groupSoldeInitial->isEnabled()) {
            QString nomCompteCapitaux = ui->choixCompteCapitaux->currentText();
            if(nomCompteCapitaux.isNull() || nomCompteCapitaux.isEmpty()) {
                QMessageBox::critical(this, "Erreur de création", "Vous devez créer un compte de capitaux pour le solde initial du compte !");
                return;
            }
            double soldeInitial = ui->spinBoxMontant->value();
            if(ui->choixClasse->isEnabled()) {
                ClasseCompte classeCompte = getClasseCompte(ui->choixClasse->currentText());
                manager.ajouterCompte(nomCompte, classeCompte, soldeInitial, nomCompteCapitaux);
            } else {
                QString nomParent = ui->choixCompteParent->currentText();
                manager.ajouterCompte(nomCompte, nomParent, soldeInitial, nomCompteCapitaux);
            }
        } else {
            bool virtuel = ui->checkboxVirtuel->isChecked();
            if(ui->choixClasse->isEnabled()) {
                ClasseCompte classeCompte = getClasseCompte(ui->choixClasse->currentText());
                manager.ajouterCompte(nomCompte, classeCompte, virtuel);
            } else {
                QString nomParent = ui->choixCompteParent->currentText();
                manager.ajouterCompte(nomCompte, nomParent, virtuel);
            }
        }
        close();
    } catch(const CompteException& e) {
        QMessageBox::critical(this, "Erreur de création", e.what());
    }
}

void CreationCompteDialog::on_choixClasse_currentIndexChanged(int) {
    updateGroupeSoldeInitial();
}

void CreationCompteDialog::on_boutonAjouterCompteCapitaux_clicked() {
    CreationCompteCapitauxDialog* dialog = new CreationCompteCapitauxDialog(this);
    connect(dialog, SIGNAL(compteCapitauxCree(const QString&)), this, SLOT(ajouterCompteCapitaux(const QString&)));
    dialog->exec();
}

void CreationCompteDialog::ajouterCompteCapitaux(const QString& nomCompte) {
    ui->choixCompteCapitaux->addItem(nomCompte);
}
