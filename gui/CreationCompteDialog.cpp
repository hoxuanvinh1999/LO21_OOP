#include "CreationCompteDialog.h"
#include "ui_CreationCompteDialog.h"

CreationCompteDialog::CreationCompteDialog(QWidget *parent): QDialog(parent), ui(new Ui::CreationCompteDialog) {
    ui->setupUi(this);
}

CreationCompteDialog::~CreationCompteDialog() {
    delete ui;
}
