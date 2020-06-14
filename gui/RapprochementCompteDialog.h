#ifndef RAPPROCHEMENTCOMPTEDIALOG_H
#define RAPPROCHEMENTCOMPTEDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class RapprochementCompteDialog;
}

/**
 * @class RapprochementCompteDialog
 * @brief Classe correspondant à une fenêtre de rapprochement d'un compte.
 */
class RapprochementCompteDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de rapprochement d'un compte.
     * @param parent Widget parent de la fenêtre.
     */
    explicit RapprochementCompteDialog(QWidget *parent = nullptr);
    /**
      * Destructeur d'une fenêtre de rapprochement d'un compte.
      */
    ~RapprochementCompteDialog();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Rapprocher".
     */
    void on_boutonRapprocher_clicked();
    /**
     * @brief Slot déclenché lors du changement du choix de compte.
     */
    void on_choixCompte_currentIndexChanged(int);
    /**
     * @brief Slot déclenché lors du changement du choix de date.
     */
    void on_choixDate_userDateChanged(const QDate&);

private:
    /**
     * @brief Interface graphique d'une fenêtre de rapprochement d'un compte.
     */
    Ui::RapprochementCompteDialog* ui;
    /**
     * @brief Gestionnaire de comptabilité d'une fenêtre de rapproche d'un compte.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Défini les choix des comptes possibles.
     */
    void definirChoixComptes();
    /**
     * @brief Redéfini les choix des dates possibles.
     */
    void definirChoixDate();
    /**
     * @brief Redéfini les informations de rapprochement du compte selectionné.
     */
    void definirInformationsRapprochement();
    /**
     * @brief Redéfini le solde à la date donnée du compte selectionné.
     */
    void definirSoldeDateDonnee();
};

#endif // RAPPROCHEMENTCOMPTEDIALOG_H
