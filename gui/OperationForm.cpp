#include "OperationForm.h"
#include "ui_OperationForm.h"

OperationForm::OperationForm(QWidget *parent, bool fermable): QWidget(parent), ui(new Ui::OperationForm), fermable(fermable), manager(ComptabiliteManager::getInstance())  {
    ui->setupUi(this);
    ui->boutonFermer->setEnabled(fermable);
    ajouterChoixComptes();
}

OperationForm::~OperationForm() {
    delete ui;
}

void OperationForm::ajouterChoixComptes() {
    ui->choixCompte->clear();
    for(const CompteAbstrait& compte : manager.comptes()) {
        if(compte.getType() == SIMPLE) {
            ui->choixCompte->addItem(compte.getNom());
        }
    }
}

void OperationForm::setFermable(bool fermable) {
    this->fermable = fermable;
    ui->boutonFermer->setEnabled(fermable);
}

void OperationForm::on_boutonFermer_clicked() {
    emit suppression();
    close();
}

Operation OperationForm::getOperation() {
    return Operation(ui->choixMontant->value(), getTypeOperation(ui->choixType->currentText()), ui->choixCompte->currentText());
}
