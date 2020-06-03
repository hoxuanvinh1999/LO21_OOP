#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "core/ComptabiliteManager.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include "core/SauvegardeException.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fermerSessionActuelle() {
    demanderSauvegarde();
    ComptabiliteManager::libererInstance();
    ui->actionSauvegarder->setEnabled(false);
    ui->actionSauvegarderEnTantQue->setEnabled(false);
    ui->actionFermerSession->setEnabled(false);
    ui->actionGenererBilan->setEnabled(false);
    ui->actionGenererReleve->setEnabled(false);
    ui->actionGenererResultat->setEnabled(false);
    delete comptabiliteForm;
    comptabiliteForm = nullptr;
}

void MainWindow::ouvrirNouvelleSession(const QString& filename) {
    ComptabiliteManager::charger(filename);
    ui->actionSauvegarder->setEnabled(true);
    ui->actionSauvegarderEnTantQue->setEnabled(true);
    ui->actionFermerSession->setEnabled(true);
    ui->actionGenererBilan->setEnabled(true);
    ui->actionGenererReleve->setEnabled(true);
    ui->actionGenererResultat->setEnabled(true);
    comptabiliteForm = new ComptabiliteForm(this);
    this->centralWidget()->layout()->addWidget(comptabiliteForm);
}

void MainWindow::demanderSauvegarde() {
    if(ComptabiliteManager::estInstancie()) {
        bool fin = false;
        while(!fin) {
            QMessageBox msgBox(QMessageBox::Information, "Sauvegarde de vos données", "Souhaitez vous sauvegarder les données sur lequel vous travaillez actuellement ?", QMessageBox::Yes | QMessageBox::No, this);
            msgBox.setButtonText(QMessageBox::Yes, "Oui");
            msgBox.setButtonText(QMessageBox::No, "Non");
            QMessageBox::StandardButton reponse = static_cast<QMessageBox::StandardButton>(msgBox.exec());
            if(reponse == QMessageBox::Yes) {
                fin = sauvegarder();
            } else {
                fin = true;
            }
        }
    }
}

bool MainWindow::sauvegarder() {
    ComptabiliteManager& manager = ComptabiliteManager::getInstance();
    if(manager.getNomFichier().isNull()) {
        return sauvegarderEnTantQue();
    } else {
        try {
            manager.sauvegarder();
        } catch(const SauvegardeException& e) {
            QMessageBox::critical(this, "Erreur de sauvegarde", e.what());
            return false;
        }
        return true;
    }
}

bool MainWindow::sauvegarderEnTantQue() {
    ComptabiliteManager& manager = ComptabiliteManager::getInstance();
    while(true) {
        QString filename = QFileDialog::getSaveFileName(this, "Sauvegarde de vos données", "", "Fichier de sauvegarde (*.xml);;Tout fichier (*)");
        if(!filename.isEmpty()) {
            try {
                manager.sauvegarder(filename);
                return true;
            } catch(const SauvegardeException& e) {
                QMessageBox::critical(this, "Erreur de sauvegarde", e.what());
            }
        } else {
            return false;
        }
    }
}

void MainWindow::on_actionQuitter_triggered() {
    demanderSauvegarde();
    close();
}

void MainWindow::on_actionNouveau_triggered() {
    fermerSessionActuelle();
    ouvrirNouvelleSession();
}

void MainWindow::on_actionCharger_triggered() {
    fermerSessionActuelle();
    QString filename = QFileDialog::getOpenFileName(this, "Ouvrir fichier de sauvegarde", "", "Fichier de sauvegarde (*.xml);;Tout fichier (*)");
    if(!filename.isEmpty()) {
        ouvrirNouvelleSession(filename);
    }
}

void MainWindow::on_actionFermerSession_triggered() {
    fermerSessionActuelle();
}

void MainWindow::on_actionSauvegarder_triggered() {
    if(ComptabiliteManager::estInstancie()) {
        sauvegarder();
    }
}

void MainWindow::on_actionSauvegarderEnTantQue_triggered() {
    if(ComptabiliteManager::estInstancie()) {
        sauvegarderEnTantQue();
    }
}

void MainWindow::closeEvent(QCloseEvent*) {
    demanderSauvegarde();
}

void MainWindow::on_actionGenererBilan_triggered() {

}

void MainWindow::on_actionGenererReleve_triggered() {

}

void MainWindow::on_actionGenererResultat_triggered() {

}
