#include "SuppressionTransactionDialog.h"
#include "ui_SuppressionTransactionDialog.h"
#include <QMessageBox>

SuppressionTransactionDialog::SuppressionTransactionDialog(QWidget *parent): QDialog(parent), ui(new Ui::SuppressionTransactionDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->layoutChoixTransaction->setAlignment(Qt::AlignHCenter);
    definirChoixTransactions();
}

SuppressionTransactionDialog::~SuppressionTransactionDialog() {
    delete ui;
}

void SuppressionTransactionDialog::definirChoixTransactions() {
    ui->choixTransaction->clear();
    for(const Transaction& transaction : manager.transactions()) {
        if(!transaction.estFigee()) {
            ui->choixTransaction->addItem(transaction.getReference());
        }
    }
}

void SuppressionTransactionDialog::on_boutonFermer_clicked() {
    close();
}

void SuppressionTransactionDialog::on_boutonSupprimer_clicked() {
    try {
        manager.supprimerTransaction(ui->choixTransaction->currentText());
        close();
    } catch(const exception& e) {
        QMessageBox::critical(this, "Erreur de suppression", e.what());
    }
}
