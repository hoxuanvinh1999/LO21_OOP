#include "TransactionsForm.h"
#include "ui_TransactionsForm.h"
#include "CreationTransactionDialog.h"
#include "SuppressionTransactionDialog.h"
#include "ModificationTransactionDialog.h"
#include "core/TransactionException.h"
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

void TransactionsForm::chargerEtat(Configuration& config) {
    int indexTransaction = ui->choixTransaction->findText(config.getValeurAttribut("reference_transaction_actuelle"));
    if(indexTransaction != -1) {
        ui->choixTransaction->setCurrentIndex(indexTransaction);
    }
}

void TransactionsForm::sauvegarderEtat(Configuration& config) const {
    config.setValeurAttribut("reference_transaction_actuelle", ui->choixTransaction->currentText());
}

void TransactionsForm::definirChoixTransactions() {
    ui->choixTransaction->clear();
    for(const Transaction& transaction : manager.getTransactions()) {
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
        int i = 0;
        for(const Operation& operation : transaction) {
            ui->tableTransaction->insertRow(i);
            double montant = operation.getMontant();
            const TypeOperation type = operation.getType();
            const CompteAbstrait& compte = manager.getCompte(operation.getNomCompte());
            ui->tableTransaction->setItem(i, 3, new QTableWidgetItem(compte.toString()));
            if(type == DEBIT) {
                ui->tableTransaction->setItem(i, 4, new QTableWidgetItem(QString::number(montant, 'f', 2) + "€"));
            } else {
                ui->tableTransaction->setItem(i, 5, new QTableWidgetItem(QString::number(montant, 'f', 2) + "€"));
            }
            ++i;
        }
        ui->tableTransaction->setItem(0, 0, new QTableWidgetItem(date.toString(Qt::LocalDate)));
        ui->tableTransaction->setItem(0, 1, new QTableWidgetItem(reference));
        ui->tableTransaction->setItem(0, 2, new QTableWidgetItem(intitule));
    }
}

void TransactionsForm::modifierAffichageTransaction(const QString& referenceTransaction) {
    if(ui->choixTransaction->currentText() == referenceTransaction)
        chargerTable();
}

void TransactionsForm::on_boutonAjouterTransaction_clicked() {
    try {
        CreationTransactionDialog* dialog = new CreationTransactionDialog(this);
        dialog->exec();
    } catch(const TransactionException& e) {
        QMessageBox::critical(this, "Erreur", e.what());
    }
}

void TransactionsForm::on_boutonSupprimerTransaction_clicked() {
    int nbTransactionsNonFigees = 0;
    for(const Transaction& transaction : manager.getTransactions()) {
        if(!transaction.estFigee()) {
            ++nbTransactionsNonFigees;
        }
    }
    if(nbTransactionsNonFigees > 0) {
        SuppressionTransactionDialog* dialog = new SuppressionTransactionDialog(this);
        dialog->exec();
    } else {
        QMessageBox::critical(this, "Erreur", "Aucune transactions supprimables !");
    }
}

void TransactionsForm::on_choixTransaction_currentIndexChanged(int) {
    chargerTable();
}

void TransactionsForm::on_boutonModifierTransaction_clicked() {
    int nbTransactionsNonFigees = 0;
    for(const Transaction& transaction : manager.getTransactions()) {
        if(!transaction.estFigee()) {
            ++nbTransactionsNonFigees;
        }
    }
    if(nbTransactionsNonFigees > 0) {
        ModificationTransactionDialog* dialog = new ModificationTransactionDialog(this);
        dialog->exec();
    } else {
        QMessageBox::critical(this, "Erreur", "Aucune transactions modifiables !");
    }
}
