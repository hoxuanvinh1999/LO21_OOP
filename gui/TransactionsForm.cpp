#include "TransactionsForm.h"
#include "ui_TransactionsForm.h"
#include "CreationTransactionDialog.h"
#include "SuppressionTransactionDialog.h"
#include <QMessageBox>

TransactionsForm::TransactionsForm(QWidget *parent): QWidget(parent), ui(new Ui::TransactionsForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    connect(&manager, SIGNAL(transactionAjoutee(const QString&)), this, SLOT(ajouterChoixTransaction(const QString&)));
    connect(&manager, SIGNAL(transactionModifiee(const QString&)), this, SLOT(modifierAffichageTransaction(const QString&)));
    connect(&manager, SIGNAL(transactionSupprimee(const QString&)), this, SLOT(supprimerChoixTransaction(const QString&)));
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

void TransactionsForm::supprimerChoixTransaction(const QString& referenceTransaction) {
    ui->choixTransaction->removeItem(ui->choixTransaction->findText(referenceTransaction));
}

void TransactionsForm::chargerTable() {
    ui->tableTransaction->model()->removeRows(0, ui->tableTransaction->rowCount());
    QString referenceTransaction = ui->choixTransaction->currentText();
    if(!referenceTransaction.isNull() && !referenceTransaction.isEmpty()) {
        const Transaction& transaction = manager.getTransaction(referenceTransaction);
        const QDate& date = transaction.getDate();
        const QString& reference = transaction.getReference();
        const QString& intitule = transaction.getIntitule();
        auto operations = transaction.operations();
        ui->tableTransaction->model()->insertRows(0, operations.size());
        ui->tableTransaction->setItem(0, 0, new QTableWidgetItem(date.toString(Qt::LocalDate)));
        ui->tableTransaction->setItem(0, 1, new QTableWidgetItem(reference));
        ui->tableTransaction->setItem(0, 2, new QTableWidgetItem(intitule));
        int i = 0;
        for(const Operation& operation : operations) {
            double montant = operation.getMontant();
            const TypeOperation type = operation.getType();
            const CompteAbstrait& compte = manager.getCompte(operation.getNomCompte());
            ui->tableTransaction->setItem(i, 3, new QTableWidgetItem(compte.toString()));
            if(type == DEBIT) {
                ui->tableTransaction->setItem(i, 4, new QTableWidgetItem(QString::number(montant) + "€"));
            } else {
                ui->tableTransaction->setItem(i, 5, new QTableWidgetItem(QString::number(montant) + "€"));
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
    if(manager.getComptesSimples().size() >= 2) {
        CreationTransactionDialog* dialog = new CreationTransactionDialog(this);
        dialog->exec();
    } else {
        QMessageBox::critical(this, "Erreur", "Il vous faut au minimum 2 comptes créés pour pouvoir effectuer un transfert !");
    }
}

void TransactionsForm::on_boutonSupprimerTransaction_clicked() {
    SuppressionTransactionDialog* dialog = new SuppressionTransactionDialog(this);
    dialog->exec();
}

void TransactionsForm::on_choixTransaction_currentIndexChanged(int) {
    chargerTable();
}
