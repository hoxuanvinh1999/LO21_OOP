#ifndef CREATIONCOMPTEDIALOG_H
#define CREATIONCOMPTEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class CreationCompteDialog;
}

class CreationCompteDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreationCompteDialog(QWidget *parent = nullptr);
    ~CreationCompteDialog();

private slots:
    void on_boutonFermer_clicked();

    void on_checkboxVirtuel_stateChanged(int arg1);

    void on_spinBoxMontant_valueChanged(double arg1);

    void on_boutonCreer_clicked();

    void on_choixCompteParent_currentIndexChanged(int index);

    void on_choixClasse_currentIndexChanged(int index);

private:
    Ui::CreationCompteDialog *ui;
    ComptabiliteManager& manager;
    void initialiserChoixComptes();
    void updateGroupeSoldeInitial();
    void updateChoixClasse();
};

#endif // CREATIONCOMPTEDIALOG_H
