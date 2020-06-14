#include "OperationForm.h"
#include "ui_OperationForm.h"

OperationForm::OperationForm(QWidget *parent, bool fermable): QWidget(parent), ui(new Ui::OperationForm), fermable(fermable), manager(ComptabiliteManager::getInstance())  {
    ui->setupUi(this);
    ui->boutonFermer->setEnabled(fermable);
    definirChoixComptes();
}

OperationForm::~OperationForm() {
    delete ui;
}

void OperationForm::definirChoixComptes() {
    ui->choixCompte->clear();
    for(const CompteAbstrait& compte : manager.getComptes()) {
        if(compte.getType() == SIMPLE) {
            ui->choixCompte->addItem(compte.getNom());
        }
    }
}

void OperationForm::setFermable(bool fermable) {
    this->fermable = fermable;
    ui->boutonFermer->setEnabled(fermable);
}

void OperationForm::setTypeOperation(const TypeOperation& typeOperation) {
    int index = ui->choixType->findText(NomsTypeOperation[typeOperation]);
    if(index != -1) {
        ui->choixType->setCurrentIndex(index);
    }
}

void OperationForm::setNomCompte(const QString& nomCompte) {
    int index = ui->choixCompte->findText(nomCompte);
    if(index != -1) {
        ui->choixCompte->setCurrentIndex(index);
    }
}

void OperationForm::setMontant(double montant) {
    ui->choixMontant->setValue(montant);
}

void OperationForm::on_boutonFermer_clicked() {
    emit suppression();
    close();
}

Operation OperationForm::getOperation() {
    return Operation(ui->choixMontant->value(), getTypeOperation(ui->choixType->currentText()), ui->choixCompte->currentText());
}
