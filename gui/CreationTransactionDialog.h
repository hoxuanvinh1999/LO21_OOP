#ifndef CREATIONTRANSACTIONDIALOG_H
#define CREATIONTRANSACTIONDIALOG_H

#include <QDialog>
#include <QSet>
#include "core/ComptabiliteManager.h"
#include "OperationForm.h"

namespace Ui {
    class CreationTransactionDialog;
}
/**
 * @brief Classe correspondant à une fenêtre de création d'une transaction.
 */
class CreationTransactionDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de création d'une transaction.
     * @param parent Widget parent de la fenêtre.
     */
    explicit CreationTransactionDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur d'une fenêtre de création d'une transaction.
      */
    ~CreationTransactionDialog();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Créer".
     */
    void on_boutonCreer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Ajouter opération".
     */
    void on_boutonAjouterOperation_clicked();
    /**
     * @brief Slot déclenché lors la suppression d'un widget opération.
     */
    void supprimerOperationForm();


private:
    /**
     * @brief Interface graphique de la fenêtre de création d'une transaction.
     */
    Ui::CreationTransactionDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de création d'une transaction.
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
     * @brief Ajoute un widget opération à la fenêtre.
     * @param operationForm Widget opération à ajouter à la fenêtre.
     */
    void ajouterOperationForm(OperationForm* operationForm);
    /**
     * @brief Redéfini l'état du bouton d'ajout d'opérations.
     */
    void definirEtatBoutonAjoutOperation();
};

#endif // CREATIONTRANSACTIONDIALOG_H
