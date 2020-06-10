#include "GenerationBilanDialog.h"
#include "ui_GenerationBilanDialog.h"
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <sstream>

GenerationBilanDialog::GenerationBilanDialog(QWidget *parent): QDialog(parent), ui(new Ui::GenerationBilanDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->choixDate->setDateTime(QDateTime::currentDateTime());
}

GenerationBilanDialog::~GenerationBilanDialog() {
    delete ui;
}

void GenerationBilanDialog::on_boutonFermer_clicked() {
    close();
}

QList<CompteSoldeNiveau> GenerationBilanDialog::getSoldesCompteEtEnfants(const CompteAbstrait& compte, const QDate& dateMax, int niveau) {
    QList<CompteSoldeNiveau> soldesComptes;
    double soldeCompte = 0;
    if(compte.getType() == SIMPLE) {
        for(const Transaction& transaction : manager.getTransactionsCompte(compte.getNom())) {
            if(transaction.getDate() <= dateMax) {
                const Operation& operation = transaction.getOperation(compte.getNom());
                if(operation.getType() == DEBIT) {
                    soldeCompte += operation.getMontant();
                } else {
                    soldeCompte -= operation.getMontant();
                }
            }
        }
    } else {
        for(const CompteAbstrait& compteEnfant : compte) {
            QList<CompteSoldeNiveau> soldesComptesEnfants = getSoldesCompteEtEnfants(compteEnfant, dateMax, niveau + 1);
            soldeCompte += soldesComptesEnfants.first().solde;
            soldesComptes.append(soldesComptesEnfants);
        }
    }
    soldesComptes.push_front({compte.toString(), niveau, soldeCompte});
    return soldesComptes;
}

void GenerationBilanDialog::on_boutonGenerer_clicked() {
    QDate date = ui->choixDate->date();
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter Bilan en PDF", "", "Fichier PDF (*.pdf);;Tout fichier (*)");
    if(!fileName.isNull() && !fileName.isEmpty()) {
        if(QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".pdf");
        }
        double soldeActifs = 0;
        double soldePassifs = 0;
        stringstream texteComptesActifs;
        stringstream texteSoldesActifs;
        stringstream texteComptesPassifs;
        stringstream texteSoldesPassifs;
        ComptabiliteManager& manager = ComptabiliteManager::getInstance();
        for(const CompteAbstrait& compteEnfant : manager.getCompteRacine()) {
            if(compteEnfant.getClasse() == ACTIF || compteEnfant.getClasse() == PASSIF) {
                QList<CompteSoldeNiveau> comptesSoldeNiveau = getSoldesCompteEtEnfants(compteEnfant, date, 0);
                stringstream* texteComptes;
                stringstream* texteSoldes;
                int multiplieur;
                if(compteEnfant.getClasse() == ACTIF) {
                    soldeActifs += comptesSoldeNiveau.first().solde;
                    texteComptes = &texteComptesActifs;
                    texteSoldes = &texteSoldesActifs;
                    multiplieur = 1;
                } else {
                    soldePassifs -= comptesSoldeNiveau.first().solde;
                    texteComptes = &texteComptesPassifs;
                    texteSoldes = &texteSoldesPassifs;
                    multiplieur = -1;
                }
                for(const CompteSoldeNiveau& compteSoldeNiveau : comptesSoldeNiveau) {
                    double soldeCompte = compteSoldeNiveau.solde * multiplieur;
                    QString nomCompte = compteSoldeNiveau.nomCompte;
                    int niveau = compteSoldeNiveau.niveau;
                    for(int i = 0; i < niveau; ++i) {
                        *texteComptes << "&nbsp;&nbsp;&nbsp;&nbsp;";
                    }
                    *texteComptes << nomCompte.toStdString() << "<br/>";
                    *texteSoldes << QString::number(soldeCompte, 'f', 2).toStdString() << "€" << "<br/>";
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
        ss << "          <th colspan=\"2\">Bilan au %0</th>";
        ss << "        </tr>";
        ss << "      </thead>";
        ss << "      <tbody>";
        ss << "        <tr>";
        ss << "          <td>%1</th>";
        ss << "          <td>%2</th>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td>%3</th>";
        ss << "          <td>%4</th>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td><b>Actifs - Passifs</b></th>";
        ss << "          <td>%5</th>";
        ss << "        </tr>";
        ss << "      </tbody>";
        ss << "    </table>";
        ss << "  </body>";
        ss << "</html>";
        QTextDocument doc;
        doc.setHtml(QString::fromStdString(ss.str()).arg(date.toString(Qt::LocalDate),
                                                         QString::fromStdString(texteComptesActifs.str()),
                                                         QString::fromStdString(texteSoldesActifs.str()),
                                                         QString::fromStdString(texteComptesPassifs.str()),
                                                         QString::fromStdString(texteSoldesPassifs.str()),
                                                         texteSoldeActifsPassifs));
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::A4);
        printer.setOutputFileName(fileName);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        doc.print(&printer);
        close();
    }
}
