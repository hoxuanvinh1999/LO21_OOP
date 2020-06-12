#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "core/ComptabiliteManager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include "core/SauvegardeException.h"
#include "GenerationBilanDialog.h"
#include "GenerationReleveDialog.h"
#include "GenerationResultatDialog.h"
#include "core/TransactionException.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::fermerSessionActuelle() {
    if(!demanderSauvegarde())
        return false;
    ComptabiliteManager::libererInstance();
    ui->actionSauvegarder->setEnabled(false);
    ui->actionSauvegarderEnTantQue->setEnabled(false);
    ui->actionFermerSession->setEnabled(false);
    ui->actionCloturerLivre->setEnabled(false);
    ui->actionGenererBilan->setEnabled(false);
    ui->actionGenererReleve->setEnabled(false);
    ui->actionGenererResultat->setEnabled(false);
    delete comptabiliteForm;
    comptabiliteForm = nullptr;
    return true;
}

void MainWindow::ouvrirNouvelleSession(const QString& filename) {
    ComptabiliteManager::charger(filename);
    ui->actionSauvegarder->setEnabled(true);
    ui->actionSauvegarderEnTantQue->setEnabled(true);
    ui->actionFermerSession->setEnabled(true);
    ui->actionCloturerLivre->setEnabled(true);
    ui->actionGenererBilan->setEnabled(true);
    ui->actionGenererReleve->setEnabled(true);
    ui->actionGenererResultat->setEnabled(true);
    comptabiliteForm = new ComptabiliteForm(this);
    this->centralWidget()->layout()->addWidget(comptabiliteForm);

}

bool MainWindow::demanderSauvegarde() {
    if(ComptabiliteManager::estInstancie() && !ComptabiliteManager::getInstance().estSauvegarde()) {
        bool fin = false;
        while(!fin) {
            QMessageBox msgBox(QMessageBox::Information, "Sauvegarde de vos données", "Souhaitez vous sauvegarder les données sur lequel vous travaillez actuellement ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
            msgBox.setButtonText(QMessageBox::Yes, "Oui");
            msgBox.setButtonText(QMessageBox::No, "Non");
            msgBox.setButtonText(QMessageBox::Cancel, "Annuler");
            QMessageBox::StandardButton reponse = static_cast<QMessageBox::StandardButton>(msgBox.exec());
            if(reponse == QMessageBox::Yes) {
                fin = sauvegarder();
            } else if(reponse == QMessageBox::No) {
                fin = true;
            } else {
                return false;
            }
        }
    }
    return true;
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
    if(demanderSauvegarde()) {
        close();
    }
}

void MainWindow::on_actionNouveau_triggered() {
    if(fermerSessionActuelle()) {
        ouvrirNouvelleSession();
    }
}

void MainWindow::on_actionCharger_triggered() {
    if(fermerSessionActuelle()) {
        bool fin = false;
        while(!fin) {
            QString filename = QFileDialog::getOpenFileName(this, "Ouvrir fichier de sauvegarde", "", "Fichier de sauvegarde (*.xml);;Tout fichier (*)");
            if(!filename.isEmpty()) {
                try {
                    ouvrirNouvelleSession(filename);
                    fin = true;
                } catch(const SauvegardeException& e) {
                    QMessageBox::critical(this, "Erreur de chargement", e.what());
                }
            } else {
                fin = true;
            }
        }
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

void MainWindow::closeEvent(QCloseEvent* e) {
    if(!demanderSauvegarde()) {
        e->ignore();
    }
}

void MainWindow::on_actionGenererBilan_triggered() {
    GenerationBilanDialog* dialog = new GenerationBilanDialog(this);
    dialog->exec();
}

void MainWindow::on_actionGenererReleve_triggered() {
    GenerationReleveDialog* dialog = new GenerationReleveDialog(this);
    dialog->exec();
}

void MainWindow::on_actionGenererResultat_triggered() {
    GenerationResultatDialog* dialog = new GenerationResultatDialog(this);
    dialog->exec();
}

void MainWindow::on_actionCloturerLivre_triggered() {
    QMessageBox msgBox(QMessageBox::Warning, "Effectuer la clôture du livre", "Confirmez vous la clôture du livre ?", QMessageBox::Yes | QMessageBox::No, this);
    msgBox.setButtonText(QMessageBox::Yes, "Oui");
    msgBox.setButtonText(QMessageBox::No, "Non");
    QMessageBox::StandardButton reponse = static_cast<QMessageBox::StandardButton>(msgBox.exec());
    if(reponse == QMessageBox::Yes) {
        try {
            ComptabiliteManager::getInstance().effectuerCloture();
        } catch (const TransactionException& e) {
            QMessageBox::warning(this, "Erreur", e.what());
        }
    }
}
