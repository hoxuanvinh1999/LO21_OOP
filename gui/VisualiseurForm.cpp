#include "VisualiseurForm.h"
#include "ui_VisualiseurForm.h"

VisualiseurForm::VisualiseurForm(QWidget *parent): QWidget(parent), ui(new Ui::VisualiseurForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("Comptes");
    connect(&manager, SIGNAL(comptesModifies()), this, SLOT(afficherArbre()));
    afficherArbre();
}

VisualiseurForm::~VisualiseurForm() {
    delete ui;
}

void VisualiseurForm::afficherArbre() {
    ui->treeWidget->clear();
    ajouterCompteRacine(manager.getCompteRacine());
}

void VisualiseurForm::ajouterCompteRacine(const CompteRacine& compte) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, compte.getNom());
    for(CompteAbstrait* compteEnfant : compte.getComptesEnfants()) {
        ajouterCompteEnfant(*compteEnfant, item);
    }
}

void VisualiseurForm::ajouterCompteEnfant(const CompteAbstrait& compte, QTreeWidgetItem* parent) {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QString text = QString(NomsClasseCompte[compte.getClasse()].at(0).toUpper()) + ":" + compte.getNom();
    if(compte.getType() == VIRTUEL) text += " (virtuel)";
    item->setText(0, text);
    for(CompteAbstrait* compteEnfant : compte.getComptesEnfants()) {
        ajouterCompteEnfant(*compteEnfant, item);
    }
    parent->addChild(item);
}
