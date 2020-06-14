#ifndef SUPPRESSIONTRANSACTIONDIALOG_H
#define SUPPRESSIONTRANSACTIONDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class SuppressionTransactionDialog;
}

/**
 * @class SuppressionTransactionDialog
 * @brief Classe correspondant à une fenêtre de suppression d'une transaction.
 */
class SuppressionTransactionDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de suppression d'une transactions.
     * @param parent Widget parent de la fenêtre.
     */
    explicit SuppressionTransactionDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur d'une fenêtre de suppression d'une transaction.
      */
    ~SuppressionTransactionDialog();

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
     * @brief Interface graphique d'une fenêtre de suppression d'une transaction.
     */
    Ui::SuppressionTransactionDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité d'une fenêtre de suppression d'une transaction.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Défini les choix de transactions possibles.
     */
    void definirChoixTransactions();
};

#endif // SUPPRESSIONTRANSACTIONDIALOG_H
