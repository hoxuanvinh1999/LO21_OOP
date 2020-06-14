#ifndef COMPTESFORM_H
#define COMPTESFORM_H

#include <QWidget>
#include "core/ComptabiliteManager.h"
#include "core/Configuration.h"

namespace Ui {
    class ComptesForm;
}

/**
 * @class ComptesForm
 * @brief Classe correspondant à l'affichage de la gestion des comptes.
 */
class ComptesForm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructeur du widget de gestion des comptes.
     * @param parent Parent du widget.
     */
    explicit ComptesForm(QWidget *parent = nullptr);
    /**
      * @brief Destructeur du widget de gestion des comptes.
      */
    ~ComptesForm();
    /**
     * @brief Charger l'état du widget de gestion des comptes à partir d'une configuration.
     * @param config Configuration à partir de laquelle charger l'état du widget de gestion des comptes.
     */
    void chargerEtat(Configuration& config);
    /**
     * @brief Sauvegarde l'état du widget de gestion des comptes dans une configuration.
     * @param config Configuration dans laquelle sauvegarder l'état du widget de gestion des comptes.
     */
    void sauvegarderEtat(Configuration& config) const;

private slots:
    /**
     * @brief Ajoute un nouveau choix de compte.
     * @param nomCompte Nom du compte à ajouter dans les choix.
     */
    void ajouterChoixCompte(const QString& nomCompte);
    /**
     * @brief Met à jour l'affichage du compte.
     * @param nomCompte Nom du compte dont il faut mettre à jour l'affichage.
     */
    void modifierAffichageCompte(const QString& nomCompte);
    /**
     * @brief Supprime un choix de compte.
     * @param nomCompte Nom du compte à supprimer des choix.
     */
    void supprimerChoixCompte(const QString& nomCompte);
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Ajouter Compte".
     */
    void on_boutonAjouterCompte_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Supprimer Compte".
     */
    void on_boutonSupprimerCompte_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Rapprocher Compte".
     */
    void on_boutonRapprocherCompte_clicked();
    /**
     * @brief Slot déclenché lors du changement de choix de compte.
     */
    void on_choixCompte_currentIndexChanged(int);

private:
    /**
     * @brief Interface graphique du widget de gestion des comptes.
     */
    Ui::ComptesForm *ui;
    /**
     * @brief Gestionnaire de comptabilité de la gestion des comptes.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Redéfini le solde du compte selectionné.
     */
    void definirSolde();
    /**
     * @brief Recharge la table des transactions du compte selectionné.
     */
    void chargerTable();
    /**
     * @brief Redéfini les choix de comptes possibles.
     */
    void definirChoixComptes();
};

#endif // COMPTESFORM_H
