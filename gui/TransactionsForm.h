#ifndef TRANSACTIONSFORM_H
#define TRANSACTIONSFORM_H

#include <QWidget>
#include "core/ComptabiliteManager.h"
#include "core/Configuration.h"

namespace Ui {
    class TransactionsForm;
}

/**
 * @class TransactionsForm
 * @brief Classe correspondant à l'affichage de la gestion des transactions.
 */
class TransactionsForm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructeur du widget de gestion des transactions.
     * @param parent Parent du widget.
     */
    explicit TransactionsForm(QWidget *parent = nullptr);
    /**
      * Destructeur du widget de gestion des transactions.
      */
    ~TransactionsForm();
    /**
     * @brief Charger l'état du widget de gestion des transactions à partir d'une configuration.
     * @param config Configuration à partir de laquelle charger l'état du widget de gestion des transactions.
     */
    void chargerEtat(Configuration& config);
    /**
     * @brief Sauvegarde l'état du widget de gestion des transactions dans une configuration.
     * @param config Configuration dans laquelle sauvegarder l'état du widget de gestion des transactions.
     */
    void sauvegarderEtat(Configuration& config) const;

private slots:
    /**
     * @brief Ajoute une nouveau choix de transaction.
     * @param referenceTransaction Référence de la transaction à ajouter dans les choix.
     */
    void ajouterChoixTransaction(const QString& referenceTransaction);
    /**
     * @brief Met à jour l'affichage de la transaction.
     * @param referenceTransaction Référence de la transaction dont il faut mettre à jour l'affichage.
     */
    void modifierAffichageTransaction(const QString& referenceTransaction);
    /**
     * @brief Supprime un choix de transaction.
     * @param referenceTransaction Référence de la transaction à supprimer des choix.
     */
    void supprimerChoixTransaction(const QString& referenceTransaction);
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Ajouter Transaction".
     */
    void on_boutonAjouterTransaction_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Modifier Transaction".
     */
    void on_boutonModifierTransaction_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Supprimer Transaction".
     */
    void on_boutonSupprimerTransaction_clicked();
    /**
     * @brief Slot déclenché lors du changement de choix de transaction.
     */
    void on_choixTransaction_currentIndexChanged(int index);


private:
    /**
     * @brief Interface graphique du widget de gestion des transactions.
     */
    Ui::TransactionsForm *ui;
    /**
     * @brief Gestionnaire de comptabilité de la gestion des transactions.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Recharge la table des comptes de la transaction sélectionnée.
     */
    void chargerTable();
    /**
     * @brief Redéfini les choix de transactions possibles.
     */
    void definirChoixTransactions();
};

#endif // TRANSACTIONSFORM_H
