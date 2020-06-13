#ifndef TRANSACTIONSFORM_H
#define TRANSACTIONSFORM_H

#include <QWidget>
#include "core/ComptabiliteManager.h"
#include "core/Configuration.h"

namespace Ui {
    class TransactionsForm;
}

class TransactionsForm : public QWidget {
    Q_OBJECT

public:
    explicit TransactionsForm(QWidget *parent = nullptr);
    ~TransactionsForm();
    void chargerEtat(Configuration& config);
    void sauvegarderEtat(Configuration& config) const;

public slots:
    void ajouterChoixTransaction(const QString& referenceTransaction);

    void modifierAffichageTransaction(const QString& referenceTransaction);

    void supprimerChoixTransaction(const QString& referenceTransaction);

private slots:
    void on_boutonAjouterTransaction_clicked();

    void on_boutonSupprimerTransaction_clicked();

    void on_choixTransaction_currentIndexChanged(int index);

    void on_boutonModifierTransaction_clicked();

private:
    Ui::TransactionsForm *ui;
    ComptabiliteManager& manager;
    void chargerTable();
    void definirChoixTransactions();
};

#endif // TRANSACTIONSFORM_H
