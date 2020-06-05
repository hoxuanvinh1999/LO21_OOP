#include "CreationTransactionDialog.h"
#include "ui_CreationTransactionDialog.h"

CreationTransactionDialog::CreationTransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationTransactionDialog)
{
    ui->setupUi(this);
}

CreationTransactionDialog::~CreationTransactionDialog()
{
    delete ui;
}
