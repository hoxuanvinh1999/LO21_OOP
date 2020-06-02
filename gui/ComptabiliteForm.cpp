#include "ComptabiliteForm.h"
#include "ui_ComptabiliteForm.h"
#include "ComptesForm.h"
#include "TransactionsForm.h"
#include "VisualiseurForm.h"

ComptabiliteForm::ComptabiliteForm(QWidget *parent): QWidget(parent), ui(new Ui::ComptabiliteForm) {
    ui->setupUi(this);
    ui->tabWidget->addTab(new ComptesForm(this), "Comptes");
    ui->tabWidget->addTab(new TransactionsForm(this), "Transactions");
    ui->tabWidget->addTab(new VisualiseurForm(this), "Visualiseur");
}

ComptabiliteForm::~ComptabiliteForm() {
    delete ui;
}
