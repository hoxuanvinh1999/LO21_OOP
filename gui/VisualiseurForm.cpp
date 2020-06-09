#include "VisualiseurForm.h"
#include "ui_VisualiseurForm.h"

VisualiseurForm::VisualiseurForm(QWidget *parent): QWidget(parent), ui(new Ui::VisualiseurForm), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    ui->arbreVisualiseur->setHeaderLabel("Comptes");
    connect(&manager, SIGNAL(compteAjoute(const QString&)), this, SLOT(afficherArbre()));
    afficherArbre();
}

VisualiseurForm::~VisualiseurForm() {
    delete ui;
}

void VisualiseurForm::afficherArbre() {
    ui->arbreVisualiseur->clear();
    ajouterCompteRacine(manager.getCompteRacine());
}

void VisualiseurForm::ajouterCompteRacine(const CompteRacine& compte) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->arbreVisualiseur);
    QFont font;
    font.setBold(true);
    font.setItalic(true);
    item->setFont(0, font);
    item->setText(0, compte.getNom());
    for(const CompteAbstrait& compteEnfant : compte) {
        ajouterCompteEnfant(compteEnfant, item);
    }
}

void VisualiseurForm::ajouterCompteEnfant(const CompteAbstrait& compteEnfant, QTreeWidgetItem* parent) {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QString text = compteEnfant.toString();
    if(compteEnfant.getType() == VIRTUEL) {
        QFont font;
        font.setBold(true);
        item->setFont(0, font);
        text += " (virtuel)";
    }
    item->setText(0, text);
    for(const CompteAbstrait& compteEnfant : compteEnfant) {
        ajouterCompteEnfant(compteEnfant, item);
    }
    parent->addChild(item);
}
