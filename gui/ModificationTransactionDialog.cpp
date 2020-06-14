#include "ModificationTransactionDialog.h"
#include "ui_ModificationTransactionDialog.h"
#include <QMessageBox>

ModificationTransactionDialog::ModificationTransactionDialog(QWidget *parent): QDialog(parent), ui(new Ui::ModificationTransactionDialog), manager(ComptabiliteManager::getInstance()), operationsForms() {
    ui->setupUi(this);
    nbComptesSimplesExistants = manager.getComptes([](const CompteAbstrait& compte) { return compte.getType() == SIMPLE; }).size();
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->layoutOperations->setAlignment(Qt::AlignCenter);
    definirChoixTransactions();
    definirAffichageTransaction();
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

void ModificationTransactionDialog::definirAffichageTransaction() {
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
    definirAffichageTransaction();
}

void ModificationTransactionDialog::on_boutonAjouterOperation_clicked() {
    ajouterOperationForm(new OperationForm());
    definirEtatBoutonAjoutOperation();
}

void ModificationTransactionDialog::on_boutonCorriger_clicked() {
    QString reference = ui->choixTransaction->currentText();
    QDate date = ui->choixDate->date();
    QString intitule = ui->textIntitule->text();
    try {
        QList<Operation> operations;
        for(OperationForm* operationForm : operationsForms) {
            operations.append(operationForm->getOperation());
        }
        manager.modifierTransaction(reference, date, intitule, operations);
        close();
    } catch(const exception& e) {
        QMessageBox::critical(this, "Erreur de correction", e.what());
    }
}
