#include "TransactionsForm.h"
#include "ui_TransactionsForm.h"
#include "CreationTransactionDialog.h"

TransactionsForm::TransactionsForm(QWidget *parent): QWidget(parent), ui(new Ui::TransactionsForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    connect(&manager, SIGNAL(transactionAjoutee(const QString&)), this, SLOT(ajouterChoixTransaction(const QString&)));
    connect(&manager, SIGNAL(transactionModifiee(const QString&)), this, SLOT(modifierAffichageTransaction(const QString&)));
    definirChoixTransactions();
    chargerTable();
}

TransactionsForm::~TransactionsForm() {
    delete ui;
}

void TransactionsForm::definirChoixTransactions() {
    ui->choixTransaction->clear();
    for(const Transaction& transaction : manager.transactions()) {
        ui->choixTransaction->addItem(transaction.getReference());
    }
}

void TransactionsForm::ajouterChoixTransaction(const QString& referenceTransaction) {
    ui->choixTransaction->addItem(referenceTransaction);
}

void TransactionsForm::chargerTable() {
    ui->tableWidget->clearContents();
    QString referenceTransaction = ui->choixTransaction->currentText();
    if(!referenceTransaction.isNull() && !referenceTransaction.isEmpty()) {
        const Transaction& transaction = manager.getTransaction(referenceTransaction);
        const QDate& date = transaction.getDate();
        const QString& reference = transaction.getReference();
        const QString& intitule = transaction.getIntitule();
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(date.toString()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(reference));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(intitule));
        int i = 0;
        for(const Operation& operation : transaction) {
            double montant = operation.getMontant();
            const TypeOperation type = operation.getType();
            const CompteAbstrait& compte = manager.getCompte(operation.getNomCompte());
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(compte.toString()));
            if(type == DEBIT) {
                ui->tableWidget->setItem(i, 4, new QTableWidgetItem(montant));
            } else {
                ui->tableWidget->setItem(i, 5, new QTableWidgetItem(montant));
            }
            ++i;
        }
    }
}

void TransactionsForm::modifierAffichageTransaction(const QString& referenceTransaction) {
    if(ui->choixTransaction->currentText() == referenceTransaction)
        chargerTable();
}

void TransactionsForm::on_boutonAjouterTransaction_clicked() {
    CreationTransactionDialog* dialog = new CreationTransactionDialog(this);
    dialog->exec();
}

void TransactionsForm::on_boutonSupprimerTransaction_clicked() {

}

void TransactionsForm::on_choixTransaction_currentIndexChanged(int) {
    chargerTable();
}
