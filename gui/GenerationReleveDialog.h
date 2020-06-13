#ifndef GENERATIONRELEVEDIALOG_H
#define GENERATIONRELEVEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class GenerationReleveDialog;
}

/**
 * @brief Pop up de la génération du relevé
 */

class GenerationReleveDialog : public QDialog {
    Q_OBJECT

public:
    explicit GenerationReleveDialog(QWidget *parent = nullptr);
    ~GenerationReleveDialog();

private slots:
    void on_boutonFermer_clicked();

    void on_boutonGenerer_clicked();

    void on_choixDateDebut_userDateChanged(const QDate &date);

    void on_choixDateFin_userDateChanged(const QDate &date);

private:
    Ui::GenerationReleveDialog *ui;
    ComptabiliteManager& manager;
};

#endif // GENERATIONRELEVEDIALOG_H
