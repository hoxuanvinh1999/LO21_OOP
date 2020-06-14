#ifndef GENERATIONRELEVEDIALOG_H
#define GENERATIONRELEVEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class GenerationReleveDialog;
}

/**
 * @class GenerationReleveDialog
 * @brief Classe correspondant à une fenêtre de génération de relevé.
 */
class GenerationReleveDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructure d'une fenêtre de génération de relevé.
     * @param parent Widget parent de la fenêtre.
     */
    explicit GenerationReleveDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur de la fenêtre de génération de relevé.
      */
    ~GenerationReleveDialog();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Générer".
     */
    void on_boutonGenerer_clicked();
    /**
     * @brief Slot déclenché lors du changement de choix de date de début de relevé
     * @param date Nouvelle date de début du relevé
     */
    void on_choixDateDebut_userDateChanged(const QDate &date);
    /**
     * @brief Slot déclenché lors du changement de choix de date de fin de relevé
     * @param date Nouvelle date de fin du relevé
     */
    void on_choixDateFin_userDateChanged(const QDate &date);

private:
    /**
     * @brief ui Interface graphique de la fenêtre de génération de relevé.
     */
    Ui::GenerationReleveDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de génération de relevé.
     */
    ComptabiliteManager& manager;
};

#endif // GENERATIONRELEVEDIALOG_H
