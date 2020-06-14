#ifndef GENERATIONRESULTATDIALOG_H
#define GENERATIONRESULTATDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class GenerationResultatDialog;
}

/**
 * @class GenerationResultatDialog
 * @brief Classe correspondant à une fenêtre de génération de résultat.
 */
class GenerationResultatDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructure d'une fenêtre de génération de résultat.
     * @param parent Widget parent de la fenêtre.
     */
    explicit GenerationResultatDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur de la fenêtre de génération de résultat.
      */
    ~GenerationResultatDialog();

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
     * @brief Slot déclenché lors du changement de choix de date de début de résultat
     * @param date Nouvelle date de début du relevé
     */
    void on_choixDateDebut_userDateChanged(const QDate &date);
    /**
     * @brief Slot déclenché lors du changement de choix de date de fin de résultat
     * @param date Nouvelle date de fin du relevé
     */
    void on_choixDateFin_userDateChanged(const QDate &date);

private:
    /**
     * @brief Interface graphique de la fenêtre de génération de résultat.
     */
    Ui::GenerationResultatDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de génération de résultat.
     */
    ComptabiliteManager& manager;
};

#endif // GENERATIONRESULTATDIALOG_H
