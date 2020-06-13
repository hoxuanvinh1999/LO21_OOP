#include "ComptabiliteForm.h"
#include "ui_ComptabiliteForm.h"

ComptabiliteForm::ComptabiliteForm(QWidget *parent): QWidget(parent), ui(new Ui::ComptabiliteForm), comptesTab(new ComptesForm(this)), transactionsTab(new TransactionsForm(this)), visualiseurTab(new VisualiseurForm(this)) {
    ui->setupUi(this);
    ui->tabWidget->addTab(comptesTab, "Comptes");
    ui->tabWidget->addTab(transactionsTab, "Transactions");
    ui->tabWidget->addTab(visualiseurTab, "Visualiseur");
}

ComptabiliteForm::~ComptabiliteForm() {
    delete ui;
}

void ComptabiliteForm::chargerEtat(Configuration& config) {
    QString nomTabActuelle = config.getValeurAttribut("nom_tab_actuelle");
    int nbTabs = ui->tabWidget->count();
    for(int i = 0; i < nbTabs; ++i) {
        if(ui->tabWidget->tabText(i) == nomTabActuelle) {
            ui->tabWidget->setCurrentIndex(i);
            break;
        }
    }
    comptesTab->chargerEtat(config);
    transactionsTab->chargerEtat(config);
}

void ComptabiliteForm::sauvegarderEtat(Configuration& config) const {
    config.setValeurAttribut("nom_tab_actuelle", ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
    comptesTab->sauvegarderEtat(config);
    transactionsTab->sauvegarderEtat(config);
}
