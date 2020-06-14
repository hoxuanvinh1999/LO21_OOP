#include "RapprochementCompteDialog.h"
#include "ui_RapprochementCompteDialog.h"
#include <QMessageBox>

RapprochementCompteDialog::RapprochementCompteDialog(QWidget *parent): QDialog(parent), ui(new Ui::RapprochementCompteDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    definirChoixComptes();
    ui->choixDate->setDate(QDate::currentDate());
    definirInformationsRapprochement();
    definirChoixDate();
    definirSoldeDateDonnee();
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
}

void RapprochementCompteDialog::definirInformationsRapprochement() {
    const CompteAbstrait& compte = manager.getCompte(ui->choixCompte->currentText());
    QDate dateDernierRapprochement = compte.getDateDernierRapprochement();
    if(!dateDernierRapprochement.isNull() && dateDernierRapprochement.isValid()) {
        ui->dateDernierRapprochement->setText(dateDernierRapprochement.toString(Qt::LocalDate));
    } else {
        ui->dateDernierRapprochement->setText("");
    }
    ui->soldeDernierRapprochement->setText(QString::number(compte.getSoldeDernierRapprochement(), 'f', 2) + "€");
}

void RapprochementCompteDialog::definirSoldeDateDonnee() {
    QString nomCompte = ui->choixCompte->currentText();
    QDate dateRapprochement = ui->choixDate->date();
    double soldeDateDonnee = manager.getSoldeCalculeCompte(nomCompte, [dateRapprochement](const Transaction& transaction) { return transaction.getDate() <= dateRapprochement; });
    ui->soldeDateDonnee->setText(QString::number(soldeDateDonnee, 'f', 2) + "€");
}

void RapprochementCompteDialog::on_choixCompte_currentIndexChanged(int) {
    definirInformationsRapprochement();
    definirChoixDate();
    definirSoldeDateDonnee();
}

void RapprochementCompteDialog::on_choixDate_userDateChanged(const QDate&) {
    definirSoldeDateDonnee();
}

void RapprochementCompteDialog::on_boutonRapprocher_clicked() {
    QString nomCompte = ui->choixCompte->currentText();
    QDate dateRapprochement = ui->choixDate->date();
    try {
        manager.rapprocherCompte(nomCompte, dateRapprochement);
        close();
    } catch(const CompteException& e) {
        QMessageBox::critical(this, "Erreur de rapprochement", e.what());
    }
}
