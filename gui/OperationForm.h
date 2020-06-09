#ifndef OPERATIONFORM_H
#define OPERATIONFORM_H

#include <QWidget>
#include "core/ComptabiliteManager.h"

namespace Ui {
    class OperationForm;
}

class OperationForm : public QWidget {
    Q_OBJECT

public:
    explicit OperationForm(QWidget *parent = nullptr, bool fermable = true);
    ~OperationForm();
    bool estFermable() const { return fermable; }
    Operation getOperation();

public slots:
    void setFermable(bool fermable);
    void setTypeOperation(const TypeOperation& typeOperation);
    void setNomCompte(const QString& nomCompte);
    void setMontant(double montant);

signals:
    void suppression();

private slots:
    void on_boutonFermer_clicked();

private:
    Ui::OperationForm *ui;
    bool fermable;
    ComptabiliteManager& manager;
    void ajouterChoixComptes();
};

#endif // OPERATIONFORM_H
