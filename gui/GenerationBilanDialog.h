#ifndef GENERATIONBILANDIALOG_H
#define GENERATIONBILANDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class GenerationBilanDialog;
}

/**
 * @brief Pop up de la génération du bilan
 */

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
};

#endif // GENERATIONBILANDIALOG_H
