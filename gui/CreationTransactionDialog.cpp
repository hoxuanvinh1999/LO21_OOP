#include "CreationTransactionDialog.h"
#include "ui_CreationTransactionDialog.h"
#include "core/TransactionException.h"
#include <QMessageBox>

CreationTransactionDialog::CreationTransactionDialog(QWidget *parent): QDialog(parent), ui(new Ui::CreationTransactionDialog), manager(ComptabiliteManager::getInstance()), operationsForms() {
    nbComptesSimplesExistants = manager.getComptes([](const CompteAbstrait& compte) { return compte.getType() == SIMPLE; }).size();
    if(nbComptesSimplesExistants < 2)
        throw TransactionException("Il vous faut au minimum 2 comptes créés pour pouvoir effectuer un transfert !");
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->choixDate->setDateTime(QDateTime::currentDateTime());
    ui->layoutOperations->setAlignment(Qt::AlignCenter);
    ajouterOperationForm(new OperationForm(nullptr, false));
    ajouterOperationForm(new OperationForm(nullptr, false));
    definirEtatBoutonAjoutOperation();
}

CreationTransactionDialog::~CreationTransactionDialog() {
    delete ui;
}

void CreationTransactionDialog::on_boutonFermer_clicked() {
    close();
}

void CreationTransactionDialog::on_boutonAjouterOperation_clicked() {
    ajouterOperationForm(new OperationForm());
    definirEtatBoutonAjoutOperation();
}

void CreationTransactionDialog::ajouterOperationForm(OperationForm* operationForm) {
    operationsForms.insert(operationForm);
    ui->layoutOperations->addWidget(operationForm);
    connect(operationForm, SIGNAL(suppression()), this, SLOT(supprimerOperationForm()));
}

void CreationTransactionDialog::supprimerOperationForm() {
    operationsForms.remove(static_cast<OperationForm*>(sender()));
    ui->boutonAjouterOperation->setEnabled(true);
}

void CreationTransactionDialog::definirEtatBoutonAjoutOperation() {
    ui->boutonAjouterOperation->setEnabled(operationsForms.size() < nbComptesSimplesExistants);
}

void CreationTransactionDialog::on_boutonCreer_clicked() {
    QDate date = ui->choixDate->date();
    QString reference = ui->textReference->text();
    QString intitule = ui->textIntitule->text();
    try {
        QList<Operation> operations;
        for(OperationForm* operationForm : operationsForms) {
            operations.append(operationForm->getOperation());
        }
        manager.ajouterTransaction(date, reference, intitule, operations);
        close();
    } catch(const exception& e) {
        QMessageBox::critical(this, "Erreur de création", e.what());
    }
}
