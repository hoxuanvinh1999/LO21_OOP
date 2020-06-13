#ifndef CREATIONTRANSACTIONDIALOG_H
#define CREATIONTRANSACTIONDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"
#include "OperationForm.h"

namespace Ui {
    class CreationTransactionDialog;
}

/**
 * @brief Pop up de la création d'une transaction
 */

class CreationTransactionDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreationTransactionDialog(QWidget *parent = nullptr);
    ~CreationTransactionDialog();

private slots:
    void on_boutonFermer_clicked();

    void on_boutonAjouterOperation_clicked();

    void supprimerOperationForm();

    void on_boutonCreer_clicked();

private:
    Ui::CreationTransactionDialog *ui;
    ComptabiliteManager& manager;
    QSet<OperationForm*> operationsForms;
    int nbComptesSimplesExistants;
    void ajouterOperationForm(OperationForm* operationForm);
    void definirEtatBoutonAjoutOperation();
};

#endif // CREATIONTRANSACTIONDIALOG_H
