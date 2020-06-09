#ifndef SUPPRESSIONCOMPTEDIALOG_H
#define SUPPRESSIONCOMPTEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class SuppressionCompteDialog;
}

class SuppressionCompteDialog : public QDialog {
    Q_OBJECT

public:
    explicit SuppressionCompteDialog(QWidget *parent = nullptr);
    ~SuppressionCompteDialog();

private slots:
    void on_boutonFermerFenetre_clicked();

    void on_boutonSupprimerCompte_clicked();

private:
    Ui::SuppressionCompteDialog *ui;
    ComptabiliteManager& manager;
    void definirChoixComptes();
};

#endif // SUPPRESSIONCOMPTEDIALOG_H
