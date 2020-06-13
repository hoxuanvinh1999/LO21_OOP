#ifndef COMPTABILITEFORM_H
#define COMPTABILITEFORM_H

#include <QWidget>
#include "core/Configuration.h"
#include "ComptesForm.h"
#include "TransactionsForm.h"
#include "VisualiseurForm.h"

namespace Ui {
class ComptabiliteForm;
}

class ComptabiliteForm : public QWidget {
    Q_OBJECT

public:
    explicit ComptabiliteForm(QWidget *parent = nullptr);
    ~ComptabiliteForm();
    void chargerEtat(Configuration& config);
    void sauvegarderEtat(Configuration& config) const;

private:
    Ui::ComptabiliteForm *ui;
    ComptesForm* comptesTab = nullptr;
    TransactionsForm* transactionsTab = nullptr;
    VisualiseurForm* visualiseurTab = nullptr;

};

#endif // COMPTABILITEFORM_H
