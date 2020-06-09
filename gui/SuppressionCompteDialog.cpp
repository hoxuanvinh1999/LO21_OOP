#include "SuppressionCompteDialog.h"
#include "ui_SuppressionCompteDialog.h"
#include <QMessageBox>

SuppressionCompteDialog::SuppressionCompteDialog(QWidget *parent): QDialog(parent), ui(new Ui::SuppressionCompteDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    definirChoixComptes();
}

SuppressionCompteDialog::~SuppressionCompteDialog() {
    delete ui;
}

void SuppressionCompteDialog::definirChoixComptes() {
    ui->choixCompte->clear();
    for(const CompteAbstrait& compte : manager.getComptes()) {
        if(manager.compteEstSupprimable(compte.getNom())) {
            ui->choixCompte->addItem(compte.getNom());
        }
    }
}

void SuppressionCompteDialog::on_boutonFermerFenetre_clicked() {
    close();
}

void SuppressionCompteDialog::on_boutonSupprimerCompte_clicked() {
    try {
        manager.supprimerCompte(ui->choixCompte->currentText());
        close();
    } catch(const exception& e) {
        QMessageBox::critical(this, "Erreur de suppression", e.what());
    }
}
