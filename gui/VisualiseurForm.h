#ifndef VISUALISEURFORM_H
#define VISUALISEURFORM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "core/ComptabiliteManager.h"
#include "core/CompteRacine.h"
#include "core/CompteAbstrait.h"

namespace Ui {
    class VisualiseurForm;
}

/**
 * @class VisualiseurForm
 * @brief Classe correspondant à l'affichage de l'arbre des comptes.
 */
class VisualiseurForm : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructeur d'une visualiseur.
     * @param parent Widget parent du visualiseur.
     */
    explicit VisualiseurForm(QWidget *parent = nullptr);
    /**
      * Destructeur d'un visualiseur.
      */
    ~VisualiseurForm();

public slots:
    /**
     * @brief Slot permettant ré-afficher l'arbre des comptes.
     */
    void afficherArbre();

private:
    /**
     * @brief Interface graphique d'un visualiseur.
     */
    Ui::VisualiseurForm *ui;
    /**
     * @brief Gestionnaire de comptabilité d'un visualiseur.
     */
    ComptabiliteManager& manager;
    /**
     * @brief Ajoute un compte racine et ses sous comptes à l'arbre de visualisation.
     * @param compte Compte racine dont on veut afficher l'arbre.
     */
    void ajouterCompteRacine(const CompteRacine& compte);
    /**
     * @brief Ajoute un compte et ses enfants à l'arbre de visualisation.
     * @param compte Compte à ajouter à l'arbre.
     * @param parent Widget parent dans l'arbre.
     */
    void ajouterCompteEnfant(const CompteAbstrait& compte, QTreeWidgetItem* parent);
};

#endif // VISUALISEURFORM_H
