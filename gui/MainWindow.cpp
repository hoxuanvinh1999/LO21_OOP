#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "core/ComptabiliteManager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPrinter>
#include <QTextDocument>
#include <QStack>
#include <QPair>
#include <sstream>
#include "core/SauvegardeException.h"


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
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter Bilan en PDF", "", "Fichier PDF (*.pdf);;Tout fichier (*)");
    if(!fileName.isNull() && !fileName.isEmpty()) {
        if(QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".pdf");
        }
        ComptabiliteManager& manager = ComptabiliteManager::getInstance();
        QStack<QPair<int, const CompteAbstrait*>> pairesNiveauCompte;
        for(const CompteAbstrait& compteEnfant : manager.getCompteRacine()) {
            pairesNiveauCompte.push(QPair<int, const CompteAbstrait*>(0, &compteEnfant));
        }
        double soldeActifs = 0;
        double soldePassifs = 0;
        stringstream texteComptesActifs;
        stringstream texteSoldesActifs;
        stringstream texteComptesPassifs;
        stringstream texteSoldesPassifs;
        while(!pairesNiveauCompte.isEmpty()) {
            QPair<int, const CompteAbstrait*> paire = pairesNiveauCompte.pop();
            int niveau = paire.first;
            const CompteAbstrait* compte = paire.second;
            if(compte->getClasse() == ACTIF || compte->getClasse() == PASSIF) {
                if(compte->getClasse() == ACTIF) {
                    if(compte->getType() == SIMPLE) {
                        soldeActifs += compte->getSolde();
                    }
                    for(int i = 0; i < niveau; ++i) {
                        texteComptesActifs << "&nbsp;&nbsp;&nbsp;&nbsp;";
                    }
                    texteComptesActifs << compte->toString().toStdString() << "<br/>";
                    texteSoldesActifs << QString::number(compte->getSolde(), 'f', 2).toStdString() << "€" << "<br/>";
                } else {
                    if(compte->getType() == SIMPLE) {
                        soldePassifs += compte->getSolde();
                    }
                    for(int i = 0; i < niveau; ++i) {
                        texteComptesPassifs << "&nbsp;&nbsp;&nbsp;&nbsp;";
                    }
                    texteComptesPassifs << compte->toString().toStdString() << "<br/>";
                    texteSoldesPassifs << QString::number(compte->getSolde(), 'f', 2).toStdString() << "€" << "<br/>";
                }
                for(const CompteAbstrait& compteEnfant : *compte) {
                    pairesNiveauCompte.push(QPair<int, const CompteAbstrait*>(niveau + 1, &compteEnfant));
                }
            }
        }
        texteComptesActifs << "<b>Total Actifs</b>";
        texteSoldesActifs << "<b>" << QString::number(soldeActifs, 'f', 2).toStdString() << "€" << "</b>";
        texteComptesPassifs << "<b>Total Passifs</b>";
        texteSoldesPassifs << "<b>" << QString::number(soldePassifs, 'f', 2).toStdString() << "€" << "</b>";
        double soldeActifsPassifs = soldeActifs - soldePassifs;
        QString texteSoldeActifsPassifs = "<b>" + QString::number(soldeActifsPassifs, 'f', 2) + "€" + "</b>";
        stringstream ss;
        ss << "<html>";
        ss << "  <head>";
        ss << "    <style>";
        ss << "      table, th, td { border: 1px solid black;} table { margin-left: auto; margin-right: auto; } body { text-align:center; }";
        ss << "    </style>";
        ss << "  </head>";
        ss << "  <body>";
        ss << "    <table>";
        ss << "      <thead>";
        ss << "        <tr>";
        ss << "          <th colspan=\"2\">Bilan</th>";
        ss << "        </tr>";
        ss << "      </thead>";
        ss << "      <tbody>";
        ss << "        <tr>";
        ss << "          <td>%0</th>";
        ss << "          <td>%1</th>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td>%2</th>";
        ss << "          <td>%3</th>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td><b>Actifs - Passifs</b></th>";
        ss << "          <td>%4</th>";
        ss << "        </tr>";
        ss << "      </tbody>";
        ss << "    </table>";
        ss << "  </body>";
        ss << "</html>";
        QTextDocument doc;
        doc.setHtml(QString::fromStdString(ss.str()).arg(QString::fromStdString(texteComptesActifs.str()), QString::fromStdString(texteSoldesActifs.str()),
                                                         QString::fromStdString(texteComptesPassifs.str()),  QString::fromStdString(texteSoldesPassifs.str()), texteSoldeActifsPassifs));
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::A4);
        printer.setOutputFileName(fileName);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        doc.print(&printer);
    }
}

void MainWindow::on_actionGenererReleve_triggered() {

}

void MainWindow::on_actionGenererResultat_triggered() {

}
