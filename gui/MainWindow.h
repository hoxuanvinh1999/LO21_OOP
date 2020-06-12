#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ComptabiliteForm.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNouveau_triggered();

    void on_actionQuitter_triggered();

    void on_actionCharger_triggered();

    void on_actionSauvegarder_triggered();

    void on_actionSauvegarderEnTantQue_triggered();

    void on_actionFermerSession_triggered();

    void on_actionGenererBilan_triggered();

    void on_actionGenererReleve_triggered();

    void on_actionGenererResultat_triggered();

    void on_actionCloturerLivre_triggered();

protected slots:
    void closeEvent(QCloseEvent* e) override;

private:
    Ui::MainWindow* ui;
    ComptabiliteForm* comptabiliteForm = nullptr;
    bool demanderSauvegarde();
    bool sauvegarder();
    bool sauvegarderEnTantQue();
    bool fermerSessionActuelle();
    void ouvrirNouvelleSession(const QString& filename = QString());
};

#endif // MAINWINDOW_H
