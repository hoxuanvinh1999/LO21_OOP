#ifndef CREATIONCOMPTECAPITAUXDIALOG_H
#define CREATIONCOMPTECAPITAUXDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class CreationCompteCapitauxDialog;
}

class CreationCompteCapitauxDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreationCompteCapitauxDialog(QWidget *parent = nullptr);
    ~CreationCompteCapitauxDialog();

signals:
    void compteCapitauxCree(const QString& nomCompte);

private slots:
    void on_boutonFermer_clicked();

    void on_boutonCreer_clicked();

private:
    Ui::CreationCompteCapitauxDialog *ui;
    ComptabiliteManager& manager;
    void initialiserChoixComptes();
};

#endif // CREATIONCOMPTECAPITAUXDIALOG_H
