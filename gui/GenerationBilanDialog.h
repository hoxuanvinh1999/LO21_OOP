#ifndef GENERATIONBILANDIALOG_H
#define GENERATIONBILANDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class GenerationBilanDialog;
}

/**
 * @class GenerationBilanDialog
 * @brief Classe correspondant à une fenêtre de génération de bilan.
 */
class GenerationBilanDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructure d'une fenêtre de génération de bilan.
     * @param parent Widget parent de la fenêtre.
     */
    explicit GenerationBilanDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur de la fenêtre de génération de bilan.
      */
    ~GenerationBilanDialog();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Générer".
     */
    void on_boutonGenerer_clicked();

private:
    /**
     * @brief Interface graphique de la fenêtre de génération de bilan.
     */
    Ui::GenerationBilanDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de génération de bilan.
     */
    ComptabiliteManager& manager;
};

#endif // GENERATIONBILANDIALOG_H
