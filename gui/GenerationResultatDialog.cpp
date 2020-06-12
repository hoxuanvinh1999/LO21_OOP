#include "GenerationResultatDialog.h"
#include "ui_GenerationResultatDialog.h"
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <sstream>
#include "core/FonctionsOutils.h"

GenerationResultatDialog::GenerationResultatDialog(QWidget *parent): QDialog(parent), ui(new Ui::GenerationResultatDialog), manager(ComptabiliteManager::getInstance()) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->choixDateDebut->setDateTime(QDateTime::currentDateTime());
    ui->choixDateDebut->setMaximumDate(ui->choixDateFin->date());
    ui->choixDateFin->setDateTime(QDateTime::currentDateTime());
    ui->choixDateFin->setMinimumDate(ui->choixDateDebut->date());
}

GenerationResultatDialog::~GenerationResultatDialog() {
    delete ui;
}

void GenerationResultatDialog::on_boutonFermer_clicked() {
    close();
}

void GenerationResultatDialog::on_boutonGenerer_clicked() {
    QDate dateDebut = ui->choixDateDebut->date();
    QDate dateFin = ui->choixDateFin->date();
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter Résultat en PDF", "", "Fichier PDF (*.pdf);;Tout fichier (*)");
    if(!fileName.isNull() && !fileName.isEmpty()) {
        if(QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".pdf");
        }
        double soldeRecettes = 0;
        double soldeDepenses = 0;
        ComptabiliteManager& manager = ComptabiliteManager::getInstance();
        for(const CompteAbstrait& compteEnfant : manager.getCompteRacine()) {
            if(compteEnfant.getClasse() == RECETTE || compteEnfant.getClasse() == DEPENSE) {
                double soldeCompte = getSoldeCalculeCompte(compteEnfant, [dateDebut, dateFin](const Transaction& transaction) { return transaction.getDate() >= dateDebut && transaction.getDate() <= dateFin; });
                if(compteEnfant.getClasse() == RECETTE) {
                    soldeRecettes += soldeCompte;
                } else {
                    soldeDepenses += soldeCompte;
                }
            }
        }
        QString texteSoldesRecettes = "<b>" + QString::number(soldeRecettes, 'f', 2) + "€" + "</b>";
        QString texteSoldesDepenses = "<b>" + QString::number(soldeDepenses, 'f', 2) + "€" + "</b>";
        double soldeRecettesDepenses = soldeRecettes - soldeDepenses;
        QString texteResultat = "<b>" + QString::number(soldeRecettesDepenses, 'f', 2) + "€" + "</b>";
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
        ss << "          <th colspan=\"2\">Résultat du %0 au %1</td>";
        ss << "        </tr>";
        ss << "      </thead>";
        ss << "      <tbody>";
        ss << "        <tr>";
        ss << "          <td><b>Total Recettes</b></td>";
        ss << "          <td>%2</th>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td><b>Total Dépenses</b></td>";
        ss << "          <td>%3</td>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td><b>Résultat</b></td>";
        ss << "          <td>%4</td>";
        ss << "        </tr>";
        ss << "        <tr>";
        ss << "          <td>%5</td>";
        ss << "          <td>%6</td>";
        ss << "        </tr>";
        ss << "      </tbody>";
        ss << "    </table>";
        ss << "  </body>";
        ss << "</html>";
        QTextDocument doc;
        doc.setHtml(QString::fromStdString(ss.str()).arg(dateDebut.toString(Qt::LocalDate),
                                                         dateFin.toString(Qt::LocalDate),
                                                         texteSoldesRecettes,
                                                         texteSoldesDepenses,
                                                         texteResultat,
                                                         texteRecettesDepenses,
                                                         texteSoldeRecettesDepenses));
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::A4);
        printer.setOutputFileName(fileName);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        doc.print(&printer);
        close();
    }
}

void GenerationResultatDialog::on_choixDateDebut_userDateChanged(const QDate& date) {
    ui->choixDateFin->setMinimumDate(date);
}

void GenerationResultatDialog::on_choixDateFin_userDateChanged(const QDate& date) {
    ui->choixDateDebut->setMaximumDate(date);
}

