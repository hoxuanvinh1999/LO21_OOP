#ifndef OPERATIONFORM_H
#define OPERATIONFORM_H

#include <QWidget>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class OperationForm;
}

/**
 * @class OperationForm
 * @brief Classe correspondant à un widget opération.
 */
class OperationForm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'un widget opération.
     * @param parent Parent du widget opération.
     * @param fermable Booléen indiquant si le widget opération est fermable ou non.
     */
    explicit OperationForm(QWidget *parent = nullptr, bool fermable = true);
    /**
      * Destructeur d'un widget opération.
      */
    ~OperationForm();
    /**
     * @brief Indique si le widget opération est fermable ou non.
     * @return Vrai si le widget opération est fermable, faux sinon.
     */
    bool estFermable() const { return fermable; }
    /**
     * @brief Récupère l'opération associée au widget opération.
     * @return L'opération associée au widget opération.
     */
    Operation getOperation();

public slots:
    /**
     * @brief Slot permettant de définir si le widget opération est fermable ou non.
     * @param fermable Booléen indiquant si le widget opération doit être fermable ou non.
     */
    void setFermable(bool fermable);
    /**
     * @brief Slot permettant de définir le type d'opération du widget opération.
     * @param typeOperation Le nouveau type d'opération du widget opération.
     */
    void setTypeOperation(const TypeOperation& typeOperation);
    /**
     * @brief Slot permettant de définir le nom du compte ciblé par l'opération du widget opération.
     * @param nomCompte Le nouveau nom du compte ciblé par l'opération du widget opération.
     */
    void setNomCompte(const QString& nomCompte);
    /**
     * @brief Slot permettant de définir le montant de l'opération du widget opération.
     * @param montant Le nouveau montant de l'opération du widget opération.
     */
    void setMontant(double montant);

signals:
    /**
     * @brief Signal émis le de la suppression du widget opération.
     */
    void suppression();

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton de fermeture du widget opération.
     */
    void on_boutonFermer_clicked();

private:
    /**
     * @brief Interface graphique d'un widget opération.
     */
    Ui::OperationForm *ui;
    /**
     * @brief Booléen indiquant si le widget opération est fermable ou non.
     */
    bool fermable;
    /**
     * @brief Gestionnaire de comptabilité du widget opération.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Défini les choix de comptes possibles.
     */
    void definirChoixComptes();
};

#endif // OPERATIONFORM_H
