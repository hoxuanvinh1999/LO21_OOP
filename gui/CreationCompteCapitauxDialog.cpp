#include "CreationCompteCapitauxDialog.h"
#include "ui_CreationCompteCapitauxDialog.h"
#include <QMessageBox>

CreationCompteCapitauxDialog::CreationCompteCapitauxDialog(QWidget *parent): QDialog(parent), ui(new Ui::CreationCompteCapitauxDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    initialiserChoixComptes();
}

CreationCompteCapitauxDialog::~CreationCompteCapitauxDialog() {
    delete ui;
}

void CreationCompteCapitauxDialog::initialiserChoixComptes() {
    for(const CompteAbstrait& compte : manager.getComptes()) {
        if((compte.getType() == VIRTUEL && compte.getClasse() == PASSIF) || compte.getType() == RACINE) {
            ui->choixCompteParent->addItem(compte.getNom());
        }
    }
}

void CreationCompteCapitauxDialog::on_boutonFermer_clicked() {
    close();
}

void CreationCompteCapitauxDialog::on_boutonCreer_clicked() {
    QString nomCompte = ui->textNom->text();
    QString nomCompteParent = ui->choixCompteParent->currentText();
    try {
        manager.ajouterCompteCapitaux(nomCompte, nomCompteParent);
        emit compteCapitauxCree(nomCompte);
        close();
    } catch(const exception& e) {
        QMessageBox::critical(this, "Erreur de création", e.what());
    }
}
