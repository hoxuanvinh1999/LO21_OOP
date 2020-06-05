#include "ComptesForm.h"
#include "ui_ComptesForm.h"
#include <QLineEdit>
#include "CreationCompteDialog.h"

ComptesForm::ComptesForm(QWidget *parent): QWidget(parent), ui(new Ui::ComptesForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    connect(&manager, SIGNAL(compteAjoute(const QString&)), this, SLOT(ajouterChoixCompte(const QString&)));
    connect(&manager, SIGNAL(compteModifie(const QString&)), this, SLOT(modifierAffichageCompte(const QString&)));
    definirChoixComptes();
    chargerTable();
    definirSolde();
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

void ComptesForm::ajouterChoixCompte(const QString& nomCompte) {
    ui->choixCompte->addItem(nomCompte);
}

void ComptesForm::chargerTable() {
    ui->tableWidget->clearContents();
    QString nomCompte = ui->choixCompte->currentText();
    auto transactions = manager.getTransactionsCompte(nomCompte);
    int i = 0;
    double solde = 0;
    for(const Transaction& transaction : transactions) {
        const QDate& date = transaction.getDate();
        const QString& reference = transaction.getReference();
        const QString& intitule = transaction.getIntitule();
        const Operation& operation = transaction.getOperation(nomCompte);
        const TypeOperation type = operation.getType();
        double montant = operation.getMontant();
        solde += montant;
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(date.toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(reference));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(intitule));
        if(type == DEBIT) {
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(montant));
        } else {
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(montant));
        }
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(solde));
        ++i;
    }
}

void ComptesForm::modifierAffichageCompte(const QString& nomCompte) {
    if(ui->choixCompte->currentText() == nomCompte)
        chargerTable();
}

void ComptesForm::definirSolde() {
    const CompteAbstrait& compte = manager.getCompte(ui->choixCompte->currentText());
    ui->textSolde->setText(QString::number(compte.getSolde(), 'g', 2) + "€");
}

void ComptesForm::on_boutonAjouterCompte_clicked() {
    CreationCompteDialog* dialog = new CreationCompteDialog(this);
    dialog->exec();
}

void ComptesForm::on_choixCompte_currentIndexChanged(int) {
    chargerTable();
    definirSolde();
}
