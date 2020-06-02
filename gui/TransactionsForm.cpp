#include "TransactionsForm.h"
#include "ui_TransactionsForm.h"

TransactionsForm::TransactionsForm(QWidget *parent): QWidget(parent), ui(new Ui::TransactionsForm) {
    ui->setupUi(this);
}

TransactionsForm::~TransactionsForm() {
    delete ui;
}
