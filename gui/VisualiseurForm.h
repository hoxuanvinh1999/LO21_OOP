#ifndef VISUALISEURFORM_H
#define VISUALISEURFORM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "core/CompteAbstrait.h"

namespace Ui {
    class VisualiseurForm;
}

class VisualiseurForm : public QWidget {
    Q_OBJECT

public:
    explicit VisualiseurForm(QWidget *parent = nullptr);
    ~VisualiseurForm();

public slots:
    void afficherArbre();

private:
    Ui::VisualiseurForm *ui;
    void ajouterCompteRacine(const CompteRacine& compte);
    void ajouterCompteEnfant(const CompteAbstrait& compte, QTreeWidgetItem* parent);
};

#endif // VISUALISEURFORM_H
