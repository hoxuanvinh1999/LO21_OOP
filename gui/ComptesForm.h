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
    void ajouterChoixCompte(const QString& nomCompte);

    void modifierAffichageCompte(const QString& nomCompte);

    void supprimerChoixCompte(const QString& nomCompte);

private slots:
    void on_boutonAjouterCompte_clicked();

    void on_choixCompte_currentIndexChanged(int);

    void on_boutonSupprimerCompte_clicked();

private:
    Ui::ComptesForm *ui;
    ComptabiliteManager& manager;
    void definirSolde();
    void chargerTable();
    void definirChoixComptes();
};

#endif // COMPTESFORM_H
