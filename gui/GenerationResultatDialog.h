#ifndef GENERATIONRESULTATDIALOG_H
#define GENERATIONRESULTATDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class GenerationResultatDialog;
}

/**
 * @brief Pop up de la génération du résultat
 */

class GenerationResultatDialog : public QDialog {
    Q_OBJECT

public:
    explicit GenerationResultatDialog(QWidget *parent = nullptr);
    ~GenerationResultatDialog();

private slots:
    void on_boutonFermer_clicked();

    void on_boutonGenerer_clicked();

    void on_choixDateDebut_userDateChanged(const QDate &date);

    void on_choixDateFin_userDateChanged(const QDate &date);

private:
    Ui::GenerationResultatDialog *ui;
    ComptabiliteManager& manager;
};

#endif // GENERATIONRESULTATDIALOG_H
