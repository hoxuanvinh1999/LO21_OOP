#ifndef CREATIONCOMPTEDIALOG_H
#define CREATIONCOMPTEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
class CreationCompteDialog;
}

/**
 * @class CreationCompteDialog
 * @brief Classe correspondant à une fenêtre de création d'un compte.
 */
class CreationCompteDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de création d'un compte.
     * @param parent Widget parent de la fenêtre.
     */
    explicit CreationCompteDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur d'une fenêtre de création d'un compte.
      */
    ~CreationCompteDialog();

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
     * @brief Slot déclenché lors de l'appui sur le bouton "Ajouter un compte de capitaux".
     */
    void on_boutonAjouterCompteCapitaux_clicked();
    /**
     * @brief Slot déclenché lors du changement d'état du checkbox "Virtuel".
     */
    void on_checkboxVirtuel_stateChanged(int);
    /**
     * @brief Slot déclenché lors du changement de valeur du spinbox "Montant".
     * @param Nouvelle valeur du montant.
     */
    void on_spinBoxMontant_valueChanged(double value);
    /**
     * @brief Slot déclenché lors du changement de choix du compte parent.
     */
    void on_choixCompteParent_currentIndexChanged(int);
    /**
     * @brief Slot déclenché lors du changement de choix de classe.
     */
    void on_choixClasse_currentIndexChanged(int);
    /**
     * @brief Slot déclenché lors de la création d'un compte de capitaux.
     * @param nomCompte Nom du compte de capitaux créé.
     */
    void ajouterCompteCapitaux(const QString& nomCompte);

private:
    /**
     * @brief ui Interface graphique de la fenêtre de création d'un compte.
     */
    Ui::CreationCompteDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de création d'un compte.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Initialise le choix des comptes possibles.
     */
    void initialiserChoixComptes();
    /**
     * @brief Redéfini l'état du groupe "Solde Initial".
     */
    void definirEtatGroupeSoldeInitial();
    /**
     * @brief Redéfini l'état du combobox "Choix Classe".
     */
    void definirEtatChoixClasse();
};

#endif // CREATIONCOMPTEDIALOG_H
