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

void GenerationBilanDialog::on_boutonGenerer_clicked() {
    QDate date = ui->choixDate->date();
    QString nomFichier = QFileDialog::getSaveFileName(this, "Exporter Bilan en PDF", "", "Fichier PDF (*.pdf);;Tout fichier (*)");
    if(!nomFichier.isNull() && !nomFichier.isEmpty()) {
        if(QFileInfo(nomFichier).suffix().isEmpty()) {
            nomFichier.append(".pdf");
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
                QList<CompteSoldeStruct> comptesSolde = manager.getSoldesCalculesCompteEtEnfants(compteEnfant.getNom(), [date](const Transaction& transaction) { return transaction.getDate() <= date; });
                stringstream* texteComptes;
                stringstream* texteSoldes;
                if(compteEnfant.getClasse() == ACTIF) {
                    soldeActifs += comptesSolde.first().solde;
                    texteComptes = &texteComptesActifs;
                    texteSoldes = &texteSoldesActifs;
                } else {
                    soldePassifs += comptesSolde.first().solde;
                    texteComptes = &texteComptesPassifs;
                    texteSoldes = &texteSoldesPassifs;
                }
                for(const CompteSoldeStruct& compteSolde : comptesSolde) {
                    double soldeCompte = compteSolde.solde;
                    QString nomCompte = compteSolde.nomCompte;
                    const CompteAbstrait& compte = manager.getCompte(nomCompte);
                    int niveau = compte.getNiveauProfondeur();
                    for(int i = 1; i < niveau; ++i) {
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
        ss << "          <td>%1</td>";
        ss << "          <td>%2</td>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td>%3</td>";
        ss << "          <td>%4</td>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td><b>Actifs - Passifs</b></td>";
        ss << "          <td>%5</td>";
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
        printer.setOutputFileName(nomFichier);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        doc.print(&printer);
        close();
    }
}
