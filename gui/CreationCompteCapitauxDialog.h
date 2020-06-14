#ifndef CREATIONCOMPTECAPITAUXDIALOG_H
#define CREATIONCOMPTECAPITAUXDIALOG_H

#include <QDialog>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class CreationCompteCapitauxDialog;
}

/**
 * @class CreationCompteCapitauxDialog
 * @brief Classe correspondant à une fenêtre de création d'un compte de capitaux.
 */
class CreationCompteCapitauxDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une fenêtre de création d'un compte de capitaux.
     * @param parent Widget parent de la fenêtre.
     */
    explicit CreationCompteCapitauxDialog(QWidget *parent = nullptr);
    /**
      * @brief Destructeur d'une fenêtre de création d'un compte de capitaux.
      */
    ~CreationCompteCapitauxDialog();

signals:
    /**
     * @brief Signal émis lors de la création d'un compte de capitaux.
     * @param nomCompte Nom du compte de capitaux créé.
     */
    void compteCapitauxCree(const QString& nomCompte);

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer".
     */
    void on_boutonFermer_clicked();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Créer".
     */
    void on_boutonCreer_clicked();

private:
    /**
     * @brief Interface graphique de la fenêtre de création d'un compte de capitaux.
     */
    Ui::CreationCompteCapitauxDialog *ui;
    /**
     * @brief Gestionnaire de comptabilité de la fenêtre de création d'un compte de capitaux.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Initialise les choix de comptes possibles.
     */
    void initialiserChoixComptes();
};

#endif // CREATIONCOMPTECAPITAUXDIALOG_H
