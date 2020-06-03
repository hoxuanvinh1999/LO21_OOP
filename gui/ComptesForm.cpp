#include "ComptesForm.h"
#include "ui_ComptesForm.h"
#include <QLineEdit>
#include "CreationCompteDialog.h"

ComptesForm::ComptesForm(QWidget *parent): QWidget(parent), ui(new Ui::ComptesForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    connect(&manager, SIGNAL(comptesModifies()), this, SLOT(definirChoixComptes()));
    definirChoixComptes();
}

ComptesForm::~ComptesForm() {
    delete ui;
}

void ComptesForm::definirChoixComptes() {
    ui->choixCompte->clear();
    for(const CompteAbstrait& compte : manager.comptes()) {
        ui->choixCompte->addItem(compte.getNom());
    }
}

void ComptesForm::chargerTable() {
    ui->tableWidget->clear();
    // TODO
}

void ComptesForm::on_boutonAjouterCompte_clicked() {
    CreationCompteDialog* dialog = new CreationCompteDialog(this);
    dialog->show();
}
