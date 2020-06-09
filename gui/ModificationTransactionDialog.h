#ifndef MODIFICATIONTRANSACTIONDIALOG_H
#define MODIFICATIONTRANSACTIONDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"
#include "OperationForm.h"

namespace Ui {
    class ModificationTransactionDialog;
}

class ModificationTransactionDialog : public QDialog {
    Q_OBJECT

public:
    explicit ModificationTransactionDialog(QWidget *parent = nullptr);
    ~ModificationTransactionDialog();

private slots:
    void on_boutonFermer_clicked();

    void supprimerOperationForm();

    void on_choixTransaction_currentIndexChanged(int index);

    void on_boutonAjouterOperation_clicked();

private:
    Ui::ModificationTransactionDialog *ui;
    ComptabiliteManager& manager;
    QSet<OperationForm*> operationsForms;
    int nbComptesSimplesExistants;
    void definirChoixTransactions();
    void updateAffichageTransaction();
    void ajouterOperationForm(OperationForm* operationForm);
    void definirEtatBoutonAjoutOperation();
};

#endif // MODIFICATIONTRANSACTIONDIALOG_H
