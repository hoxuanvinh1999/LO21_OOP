#ifndef MODIFICATIONTRANSACTIONDIALOG_H
#define MODIFICATIONTRANSACTIONDIALOG_H

#include <QDialog>
#include <QSet>
#include "core/ComptabiliteManager.h"
#include "OperationForm.h"

namespace Ui {
    class ModificationTransactionDialog;
}

/**
 * @class ModificationTransactionDialog
 * @brief Classe correspondant à une fenêtre de modification d'une transaction.
 */
class ModificationTransactionDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de modification d'une transaction.
     * @param parent Widget parent de la fenêtre.
     */
    explicit ModificationTransactionDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur d'une fenêtre de modification d'une transaction.
      */
    ~ModificationTransactionDialog();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Corriger".
     */
    void on_boutonCorriger_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Ajouter Opération".
     */
    void on_boutonAjouterOperation_clicked();
    /**
     * @brief Slot déclenché lors de la suppression d'un widget opération.
     */
    void supprimerOperationForm();
    /**
     * @brief Slot déclenché lors du changement de choix de transaction
     */
    void on_choixTransaction_currentIndexChanged(int);

private:
    /**
     * @brief Interface graphique de la fenêtre de modification d'une transation.
     */
    Ui::ModificationTransactionDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de modification d'une transaction.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Liste des widgets opérations de la fenêtre.
     */
    QSet<OperationForm*> operationsForms;
    /**
     * @brief Nombre de comptes simples existants dans le gestionnaire de comptabilité.
     */
    int nbComptesSimplesExistants;
    /**
     * @brief Défini les choix de transactions possibles.
     */
    void definirChoixTransactions();
    /**
     * @brief Redéfini l'affichage de la transaction actuelle.
     */
    void definirAffichageTransaction();
    /**
     * @brief Ajoute un widget opération à la fenêtre.
     * @param operationForm Widget opération à ajouter à la fenêtre.
     */
    void ajouterOperationForm(OperationForm* operationForm);
    /**
     * @brief Redéfini l'état du bouton d'ajout d'opérations.
     */
    void definirEtatBoutonAjoutOperation();
};

#endif // MODIFICATIONTRANSACTIONDIALOG_H
