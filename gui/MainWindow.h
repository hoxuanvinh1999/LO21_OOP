#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ComptabiliteForm.h"
#include "core/Configuration.h"

/**
 * @namespace Ui
 * @brief Namespace propre à l'interface graphique.
 */
namespace Ui {
    class MainWindow;
}

/**
 * @class MainWindow
 * @brief Classe correspondant à la fenêtre principale de l'application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la fenêtre principale de l'application.
     * @param parent Widget parent de la fenêtre.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
      * @brief Destructeur de la fenêtre principale de l'application.
      */
    ~MainWindow();
    /**
     * @brief Charger l'état de la fenêtre principale à partir d'une configuration.
     * @param config Configuration à partir de laquelle charger l'état de la fenêtre principale.
     */
    void chargerEtat(Configuration& config);
    /**
     * @brief Sauvegarde l'état de la fenêtre principale dans une configuration.
     * @param config Configuration dans laquelle sauvegarder l'état de la fenêtre principale.
     */
    void sauvegarderEtat(Configuration& config) const;

private slots:
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Nouveau" dans la barre de menu.
     */
    void on_actionNouveau_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Quitter" dans la barre de menu.
     */
    void on_actionQuitter_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Charger" dans la barre de menu.
     */
    void on_actionCharger_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Sauvegarder" dans la barre de menu.
     */
    void on_actionSauvegarder_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Sauvegarder en tant que" dans la barre de menu.
     */
    void on_actionSauvegarderEnTantQue_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Fermer session" dans la barre de menu.
     */
    void on_actionFermerSession_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Générer Bilan" dans la barre de menu.
     */
    void on_actionGenererBilan_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Générer Relevé" dans la barre de menu.
     */
    void on_actionGenererReleve_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Générer Résultat" dans la barre de menu.
     */
    void on_actionGenererResultat_triggered();
    /**
     * @brief Slot déclenché lors de l'appui sur le bouton "Clôturer livre" dans la barre de menu.
     */
    void on_actionCloturerLivre_triggered();

protected slots:
    /**
     * @brief Slot déclenché lors de la fermeture de la fenêtre principale.
     * @param e Évènement de fermeture de la fenêtre.
     */
    void closeEvent(QCloseEvent* e) override;

private:
    /**
     * @brief Interface graphique de la fenêtre principale.
     */
    Ui::MainWindow* ui;
    /**
     * @brief Widget de gestion de la comptabilité.
     */
    ComptabiliteForm* comptabiliteForm = nullptr;
    /**
     * @brief Charge la configuration de la fenêtre.
     */
    void chargerConfiguration();
    /**
     * @brief Demande à l'utilisateur de sauvegarder son travail si besoin.
     * @return Vrai si la demande s'est bien passée, faux sinon.
     */
    bool demanderSauvegarde();
    /**
     * @brief Sauvegarde le travail de l'utilisateur.
     * @return Vrai si la sauvegarde s'est bien passée, faux sinon.
     */
    bool sauvegarder();
    /**
     * @brief Sauvegarde le travail de l'utilisateur dans un fichier spécifique.
     * @return Vrai si la sauvegarde s'est bien passée, faux sinon.
     */
    bool sauvegarderEnTantQue();
    /**
     * @brief Ferme la session de travail de l'utilisateur.
     * @return Vrai si la fermeture de la session s'est bien passée, faux sinon.
     */
    bool fermerSessionActuelle();
    /**
     * @brief Ouvre une nouvelle session de travail pour l'utilisateur.
     * @param nomFichier Nom de l'éventuel fichier à faire charger le gestionnaire de comptabilité.
     */
    void ouvrirNouvelleSession(const QString& nomFichier = QString());
};

#endif // MAINWINDOW_H
