#ifndef SUPPRESSIONTRANSACTIONDIALOG_H
#define SUPPRESSIONTRANSACTIONDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class SuppressionTransactionDialog;
}

class SuppressionTransactionDialog : public QDialog {
    Q_OBJECT

public:
    explicit SuppressionTransactionDialog(QWidget *parent = nullptr);
    ~SuppressionTransactionDialog();

private slots:
    void on_boutonFermer_clicked();

    void on_boutonSupprimer_clicked();

private:
    Ui::SuppressionTransactionDialog *ui;
    ComptabiliteManager& manager;
    void definirChoixTransactions();
};

#endif // SUPPRESSIONTRANSACTIONDIALOG_H
