#ifndef SUPPRESSIONCOMPTEDIALOG_H
#define SUPPRESSIONCOMPTEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class SuppressionCompteDialog;
}

/**
 * @class SuppressionCompteDialog
 * @brief Classe correspondant à une fenêtre de suppression d'un compte.
 */
class SuppressionCompteDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de suppression d'un compte.
     * @param parent Widget parent de la fenêtre.
     */
    explicit SuppressionCompteDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur d'une fenêtre de suppression d'un compte.
      */
    ~SuppressionCompteDialog();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Supprimer".
     */
    void on_boutonSupprimer_clicked();

private:
    /**
     * @brief Interface graphique d'une fenêtre de suppression d'un compte.
     */
    Ui::SuppressionCompteDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité d'une fenêtre de suppression d'un compte.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Défini les choix des comptes possibles.
     */
    void definirChoixComptes();
};

#endif // SUPPRESSIONCOMPTEDIALOG_H
