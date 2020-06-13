#include "RapprochementCompteDialog.h"
#include "ui_RapprochementCompteDialog.h"

RapprochementCompteDialog::RapprochementCompteDialog(QWidget *parent): QDialog(parent), ui(new Ui::RapprochementCompteDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->choixDate->setDate(QDate::currentDate());
    definirChoixComptes();
}

RapprochementCompteDialog::~RapprochementCompteDialog() {
    delete ui;
}

void RapprochementCompteDialog::on_boutonFermer_clicked() {
    close();
}

void RapprochementCompteDialog::definirChoixComptes() {
    ui->choixCompte->clear();
    for(const CompteAbstrait& compte : manager.getComptes()) {
        ui->choixCompte->addItem(compte.getNom());
    }
    definirInformationsRapprochement();
    definirChoixDate();
}

void RapprochementCompteDialog::definirChoixDate() {
    const CompteAbstrait& compte = manager.getCompte(ui->choixCompte->currentText());
    if(compte.getDateDernierRapprochement().isNull()) {
        ui->choixDate->clearMinimumDate();
    } else {
        ui->choixDate->setMinimumDate(compte.getDateDernierRapprochement());
        if(ui->choixDate->date() < ui->choixDate->minimumDate())
            ui->choixDate->setDate(ui->choixDate->minimumDate());
    }
    definirSoldeDateDonnee();
}

void RapprochementCompteDialog::definirInformationsRapprochement() {
    const CompteAbstrait& compte = manager.getCompte(ui->choixCompte->currentText());
    ui->dateDernierRapprochement->setDate(compte.getDateDernierRapprochement());
    ui->soldeDernierRapprochement->setText(QString::number(compte.getSoldeDernierRapprochement(), 'f', 2) + "€");
}

void RapprochementCompteDialog::definirSoldeDateDonnee() {
    QString nomCompte = ui->choixCompte->currentText();
    QDate dateRapprochement = ui->choixDate->date();
    double soldeDateDonnee = manager.getSoldeCalculeCompte(nomCompte, [dateRapprochement](const Transaction& transaction) { return transaction.getDate() <= dateRapprochement; });
    ui->soldeDateDonnee->setText(QString::number(soldeDateDonnee, 'f', 2) + "€");
}
