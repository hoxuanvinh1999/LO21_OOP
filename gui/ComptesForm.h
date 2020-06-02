#ifndef COMPTESFORM_H
#define COMPTESFORM_H

#include <QWidget>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class ComptesForm;
}

class ComptesForm : public QWidget {
    Q_OBJECT

public:
    explicit ComptesForm(QWidget *parent = nullptr);
    ~ComptesForm();

public slots:
    void definirChoixComptes();
    void chargerTable();

private slots:
    void on_boutonAjouterCompte_clicked();

private:
    Ui::ComptesForm *ui;
    ComptabiliteManager& manager;
};

#endif // COMPTESFORM_H
