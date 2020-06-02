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

protected slots:
    void closeEvent(QCloseEvent*) override;

private:
    Ui::MainWindow* ui;
    ComptabiliteForm* comptabiliteForm = nullptr;
    void demanderSauvegarde();
    bool sauvegarder();
    bool sauvegarderEnTantQue();
    void fermerSessionActuelle();
    void ouvrirNouvelleSession(const QString& filename = QString());
};

#endif // MAINWINDOW_H
