#include "ModificationTransactionDialog.h"
#include "ui_ModificationTransactionDialog.h"

ModificationTransactionDialog::ModificationTransactionDialog(QWidget *parent): QDialog(parent), ui(new Ui::ModificationTransactionDialog), manager(ComptabiliteManager::getInstance()), operationsForms(), nbComptesSimplesExistants(manager.getComptesSimples().size()){
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    definirChoixTransactions();
    updateAffichageTransaction();
    definirEtatBoutonAjoutOperation();
}

ModificationTransactionDialog::~ModificationTransactionDialog() {
    delete ui;
}

void ModificationTransactionDialog::definirChoixTransactions() {
    ui->choixTransaction->clear();
    for(const Transaction& transaction : manager.getTransactions()) {
        if(!transaction.estFigee()) {
            ui->choixTransaction->addItem(transaction.getReference());
        }
    }
}

void ModificationTransactionDialog::updateAffichageTransaction() {
    for(OperationForm* operationForm : operationsForms) {
        delete operationForm;
    }
    operationsForms.clear();
    const Transaction& transaction = manager.getTransaction(ui->choixTransaction->currentText());
    ui->choixDate->setDate(transaction.getDate());
    ui->textIntitule->setText(transaction.getIntitule());
    int i = 1;
    for(const Operation& operation : transaction) {
        OperationForm* operationForm = new OperationForm();
        operationForm->setFermable(i > 2);
        operationForm->setTypeOperation(operation.getType());
        operationForm->setNomCompte(operation.getNomCompte());
        operationForm->setMontant(operation.getMontant());
        ajouterOperationForm(operationForm);
        ++i;
    }
}

void ModificationTransactionDialog::ajouterOperationForm(OperationForm* operationForm) {
    operationsForms.insert(operationForm);
    ui->layoutOperations->addWidget(operationForm);
    connect(operationForm, SIGNAL(suppression()), this, SLOT(supprimerOperationForm()));
}

void ModificationTransactionDialog::supprimerOperationForm() {
    operationsForms.remove(static_cast<OperationForm*>(sender()));
    ui->boutonAjouterOperation->setEnabled(true);
}

void ModificationTransactionDialog::definirEtatBoutonAjoutOperation() {
    ui->boutonAjouterOperation->setEnabled(operationsForms.size() < nbComptesSimplesExistants);
}

void ModificationTransactionDialog::on_boutonFermer_clicked() {
    close();
}

void ModificationTransactionDialog::on_choixTransaction_currentIndexChanged(int) {
    updateAffichageTransaction();
}

void ModificationTransactionDialog::on_boutonAjouterOperation_clicked() {
    ajouterOperationForm(new OperationForm());
    definirEtatBoutonAjoutOperation();
}