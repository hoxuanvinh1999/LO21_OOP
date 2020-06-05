#ifndef CREATIONTRANSACTIONDIALOG_H
#define CREATIONTRANSACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class CreationTransactionDialog;
}

class CreationTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreationTransactionDialog(QWidget *parent = nullptr);
    ~CreationTransactionDialog();

private:
    Ui::CreationTransactionDialog *ui;
};

#endif // CREATIONTRANSACTIONDIALOG_H
