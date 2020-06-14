#ifndef COMPTABILITEFORM_H
#define COMPTABILITEFORM_H

#include <QWidget>
#include "core/Configuration.h"
#include "ComptesForm.h"
#include "TransactionsForm.h"
#include "VisualiseurForm.h"

namespace Ui {
    class ComptabiliteForm;
}

/**
 * @class ComptabiliteForm
 * @brief Classe correspondant à l'affichage de la gestion de la comptabilité.
 */
class ComptabiliteForm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructeur du widget de gestion de la comptabilité.
     * @param parent Parent du widget.
     */
    explicit ComptabiliteForm(QWidget *parent = nullptr);
    /**
      * @brief Destructeur du widget de gestion de la comptabilité.
      */
    ~ComptabiliteForm();
    /**
     * @brief Charger l'état du widget de gestion de la comptabilité à partir d'une configuration.
     * @param config Configuration à partir de laquelle charger l'état du widget de gestion de la comptabilité.
     */
    void chargerEtat(Configuration& config);
    /**
     * @brief Sauvegarde l'état du widget de gestion de la comptabilité dans une configuration.
     * @param config Configuration dans laquelle sauvegarder l'état du widget de gestion de la comptabilité.
     */
    void sauvegarderEtat(Configuration& config) const;

private:
    /**
     * @brief Interface graphique du widget de gestion de la comptabilité.
     */
    Ui::ComptabiliteForm *ui;
    /**
     * @brief Widget de gestion des comptes.
     */
    ComptesForm* comptesTab = nullptr;
    /**
     * @brief Widget de gestion des transactions.
     */
    TransactionsForm* transactionsTab = nullptr;
    /**
     * @brief Widget de visualisation des comptes.
     */
    VisualiseurForm* visualiseurTab = nullptr;
};

#endif // COMPTABILITEFORM_H
