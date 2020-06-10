#ifndef GENERATIONBILANDIALOG_H
#define GENERATIONBILANDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"
#include <QList>
#include <QPair>

struct CompteSoldeNiveau {
    QString nomCompte;
    int niveau;
    double solde;
};

namespace Ui {
    class GenerationBilanDialog;
}

class GenerationBilanDialog : public QDialog {
    Q_OBJECT

public:
    explicit GenerationBilanDialog(QWidget *parent = nullptr);
    ~GenerationBilanDialog();

private slots:

    void on_boutonFermer_clicked();

    void on_boutonGenerer_clicked();

private:
    Ui::GenerationBilanDialog *ui;
    ComptabiliteManager& manager;
    QList<CompteSoldeNiveau> getSoldesCompteEtEnfants(const CompteAbstrait& compte, const QDate& dateMax, int niveau = 0);
};

#endif // GENERATIONBILANDIALOG_H
