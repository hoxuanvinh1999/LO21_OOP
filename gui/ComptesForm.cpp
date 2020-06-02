#include "ComptesForm.h"
#include "ui_ComptesForm.h"

ComptesForm::ComptesForm(QWidget *parent): QWidget(parent), ui(new Ui::ComptesForm) {
    ui->setupUi(this);
}

ComptesForm::~ComptesForm() {
    delete ui;
}
