#ifndef RAPPROCHEMENTCOMPTEDIALOG_H
#define RAPPROCHEMENTCOMPTEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class RapprochementCompteDialog;
}

class RapprochementCompteDialog : public QDialog {
    Q_OBJECT

public:
    explicit RapprochementCompteDialog(QWidget *parent = nullptr);
    ~RapprochementCompteDialog();

private slots:
    void on_boutonFermer_clicked();

private:
    Ui::RapprochementCompteDialog* ui;
    ComptabiliteManager& manager;
    void definirChoixComptes();
    void definirChoixDate();
    void definirInformationsRapprochement();
    void definirSoldeDateDonnee();
};

#endif // RAPPROCHEMENTCOMPTEDIALOG_H
