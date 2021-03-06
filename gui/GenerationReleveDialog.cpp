#include "GenerationReleveDialog.h"
#include "ui_GenerationReleveDialog.h"
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <sstream>

GenerationReleveDialog::GenerationReleveDialog(QWidget *parent): QDialog(parent), ui(new Ui::GenerationReleveDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->choixDateDebut->setDateTime(QDateTime::currentDateTime());
    ui->choixDateDebut->setMaximumDate(ui->choixDateFin->date());
    ui->choixDateFin->setDateTime(QDateTime::currentDateTime());
    ui->choixDateFin->setMinimumDate(ui->choixDateDebut->date());
}

GenerationReleveDialog::~GenerationReleveDialog() {
    delete ui;
}

void GenerationReleveDialog::on_boutonFermer_clicked() {
    close();
}

void GenerationReleveDialog::on_boutonGenerer_clicked() {
    QDate dateDebut = ui->choixDateDebut->date();
    QDate dateFin = ui->choixDateFin->date();
    QString nomFichier = QFileDialog::getSaveFileName(this, "Exporter Relevé en PDF", "", "Fichier PDF (*.pdf);;Tout fichier (*)");
    if(!nomFichier.isNull() && !nomFichier.isEmpty()) {
        if(QFileInfo(nomFichier).suffix().isEmpty()) {
            nomFichier.append(".pdf");
        }
        double soldeRecettes = 0;
        double soldeDepenses = 0;
        stringstream texteComptesRecettes;
        stringstream texteSoldesRecettes;
        stringstream texteComptesDepenses;
        stringstream texteSoldesDepenses;
        ComptabiliteManager& manager = ComptabiliteManager::getInstance();
        for(const CompteAbstrait& compteEnfant : manager.getCompteRacine()) {
            if(compteEnfant.getClasse() == RECETTE || compteEnfant.getClasse() == DEPENSE) {
                auto comptesSolde = manager.getSoldesCalculesCompteEtEnfants(compteEnfant.getNom(), [dateDebut, dateFin](const Transaction& transaction) { return transaction.getDate() >= dateDebut && transaction.getDate() <= dateFin; });
                stringstream* texteComptes;
                stringstream* texteSoldes;
                if(compteEnfant.getClasse() == RECETTE) {
                    soldeRecettes += (*comptesSolde.begin()).solde;
                    texteComptes = &texteComptesRecettes;
                    texteSoldes = &texteSoldesRecettes;
                } else {
                    soldeDepenses += (*comptesSolde.begin()).solde;
                    texteComptes = &texteComptesDepenses;
                    texteSoldes = &texteSoldesDepenses;
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
        texteComptesRecettes << "<b>Total Recettes</b>";
        texteSoldesRecettes << "<b>" << QString::number(soldeRecettes, 'f', 2).toStdString() << "€" << "</b>";
        texteComptesDepenses << "<b>Total Dépenses</b>";
        texteSoldesDepenses << "<b>" << QString::number(soldeDepenses, 'f', 2).toStdString() << "€" << "</b>";
        double soldeRecettesDepenses = soldeRecettes - soldeDepenses;
        QString texteRecettesDepenses;
        if(soldeRecettesDepenses < 0) {
            texteRecettesDepenses = "<b>Déficit</b>";
            soldeRecettesDepenses *= -1;
        } else {
            texteRecettesDepenses = "<b>Bénéfice</b>";
        }
        QString texteSoldeRecettesDepenses = "<b>" + QString::number(soldeRecettesDepenses, 'f', 2) + "€" + "</b>";
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
        ss << "          <th colspan=\"2\">Relevé du %0 au %1</th>";
        ss << "        </tr>";
        ss << "      </thead>";
        ss << "      <tbody>";
        ss << "        <tr>";
        ss << "          <td>%2</td>";
        ss << "          <td>%3</td>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td>%4</td>";
        ss << "          <td>%5</td>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td>%6</td>";
        ss << "          <td>%7</td>";
        ss << "        </tr>";
        ss << "      </tbody>";
        ss << "    </table>";
        ss << "  </body>";
        ss << "</html>";
        QTextDocument doc;
        doc.setHtml(QString::fromStdString(ss.str()).arg(dateDebut.toString(Qt::LocalDate),
                                                         dateFin.toString(Qt::LocalDate),
                                                         QString::fromStdString(texteComptesRecettes.str()),
                                                         QString::fromStdString(texteSoldesRecettes.str()),
                                                         QString::fromStdString(texteComptesDepenses.str()),
                                                         QString::fromStdString(texteSoldesDepenses.str()),
                                                         texteRecettesDepenses,
                                                         texteSoldeRecettesDepenses));
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::A4);
        printer.setOutputFileName(nomFichier);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        doc.print(&printer);
        close();
    }
}

void GenerationReleveDialog::on_choixDateDebut_userDateChanged(const QDate& date) {
    ui->choixDateFin->setMinimumDate(date);
}

void GenerationReleveDialog::on_choixDateFin_userDateChanged(const QDate& date) {
    ui->choixDateDebut->setMaximumDate(date);
}
