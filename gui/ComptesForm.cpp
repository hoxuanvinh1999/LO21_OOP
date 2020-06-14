#include "ComptesForm.h"
#include "ui_ComptesForm.h"
#include <QLineEdit>
#include "CreationCompteDialog.h"
#include "SuppressionCompteDialog.h"
#include "RapprochementCompteDialog.h"
#include <QMessageBox>

ComptesForm::ComptesForm(QWidget *parent): QWidget(parent), ui(new Ui::ComptesForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    connect(&manager, SIGNAL(compteAjoute(const QString&)), this, SLOT(ajouterChoixCompte(const QString&)));
    connect(&manager, SIGNAL(compteModifie(const QString&)), this, SLOT(modifierAffichageCompte(const QString&)));
    connect(&manager, SIGNAL(compteSupprime(const QString&)), this, SLOT(supprimerChoixCompte(const QString&)));
    definirChoixComptes();
    chargerTable();
    definirSolde();
}

ComptesForm::~ComptesForm() {
    delete ui;
}

void ComptesForm::chargerEtat(Configuration& config) {
    int indexCompte = ui->choixCompte->findText(config.getValeurAttribut("nom_compte_actuel"));
    if(indexCompte != -1) {
        ui->choixCompte->setCurrentIndex(indexCompte);
    }
}

void ComptesForm::sauvegarderEtat(Configuration& config) const {
    config.setValeurAttribut("nom_compte_actuel", ui->choixCompte->currentText());
}

void ComptesForm::definirChoixComptes() {
    ui->choixCompte->clear();
    for(const CompteAbstrait& compte : manager.getComptes()) {
        ui->choixCompte->addItem(compte.getNom());
    }
}

void ComptesForm::definirSolde() {
    const CompteAbstrait& compte = manager.getCompte(ui->choixCompte->currentText());
    ui->textSolde->setText(QString::number(compte.getSolde(), 'f', 2) + "€");
}

void ComptesForm::chargerTable() {
    ui->tableTransactionsCompte->model()->removeRows(0, ui->tableTransactionsCompte->rowCount());
    QString nomCompte = ui->choixCompte->currentText();
    auto itNomsComptes = manager.getNomCompteEtEnfants(nomCompte);
    QSet<QString> nomComptes(itNomsComptes.begin(), itNomsComptes.end());
    QList<const Transaction*> transactions;
    for(const Transaction& transaction : manager.getTransactions()) {
        for(const QString& nom : nomComptes) {
            if(transaction.impliqueCompte(nom)) {
                transactions.append(&transaction);
                break;
            }
        }
    }
    std::stable_sort(transactions.begin(), transactions.end(), [](const Transaction* a, const Transaction* b) { return a->getDate() < b->getDate(); });
    bool estRacine = nomCompte == manager.getCompteRacine().getNom();
    int i = 0;
    double solde = 0;
    for(const Transaction* transaction : transactions) {
        const QDate& date = transaction->getDate();
        const QString& reference = transaction->getReference();
        const QString& intitule = transaction->getIntitule();
        for(const Operation& operation : *transaction) {
            if(nomComptes.contains(operation.getNomCompte())) {
                ui->tableTransactionsCompte->insertRow(i);
                const CompteAbstrait& compte = manager.getCompte(operation.getNomCompte());
                const TypeOperation type = operation.getType();
                double montant = operation.getMontant();
                if(type == DEBIT) {
                    if(compte.getClasse() == ACTIF || compte.getClasse() == DEPENSE || estRacine) {
                        solde += montant;
                    } else {
                        solde -= montant;
                    }
                } else {
                    if(compte.getClasse() == ACTIF || compte.getClasse() == DEPENSE || estRacine) {
                        solde -= montant;
                    } else {
                        solde += montant;
                    }
                }
                ui->tableTransactionsCompte->setItem(i, 0, new QTableWidgetItem(date.toString(Qt::LocalDate)));
                ui->tableTransactionsCompte->setItem(i, 1, new QTableWidgetItem(reference));
                ui->tableTransactionsCompte->setItem(i, 2, new QTableWidgetItem(intitule));
                if(type == DEBIT) {
                    ui->tableTransactionsCompte->setItem(i, 3, new QTableWidgetItem(QString::number(montant, 'f', 2) + " €"));
                } else {
                    ui->tableTransactionsCompte->setItem(i, 4, new QTableWidgetItem(QString::number(montant, 'f', 2) + "€"));
                }
                ui->tableTransactionsCompte->setItem(i, 5, new QTableWidgetItem(QString::number(solde, 'f', 2) + "€"));
                ++i;
            }
        }
    }
}

void ComptesForm::ajouterChoixCompte(const QString& nomCompte) {
    ui->choixCompte->addItem(nomCompte);
}

void ComptesForm::modifierAffichageCompte(const QString& nomCompte) {
    if(ui->choixCompte->currentText() == nomCompte) {
        chargerTable();
        definirSolde();
    }
}

void ComptesForm::supprimerChoixCompte(const QString& nomCompte) {
    ui->choixCompte->removeItem(ui->choixCompte->findText(nomCompte));
}

void ComptesForm::on_boutonAjouterCompte_clicked() {
    CreationCompteDialog* dialog = new CreationCompteDialog(this);
    dialog->exec();
}

void ComptesForm::on_choixCompte_currentIndexChanged(int) {
    chargerTable();
    definirSolde();
}

void ComptesForm::on_boutonSupprimerCompte_clicked() {
    int nbComptesSupprimables = 0;
    for(const CompteAbstrait& compte : manager.getComptes()) {
        if(manager.compteEstSupprimable(compte.getNom())) {
            ++nbComptesSupprimables;
        }
    }
    if(nbComptesSupprimables > 0) {
        SuppressionCompteDialog* dialog = new SuppressionCompteDialog(this);
        dialog->exec();
    } else {
        QMessageBox::critical(this, "Erreur", "Aucun comptes supprimables !");
    }
}

void ComptesForm::on_boutonRapprocherCompte_clicked() {
    RapprochementCompteDialog* dialog = new RapprochementCompteDialog(this);
    dialog->exec();
}
