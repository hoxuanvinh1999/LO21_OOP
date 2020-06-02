#ifndef COMPTABILITEFORM_H
#define COMPTABILITEFORM_H

#include <QWidget>

namespace Ui {
    class ComptabiliteForm;
}

class ComptabiliteForm : public QWidget {
    Q_OBJECT

public:
    explicit ComptabiliteForm(QWidget *parent = nullptr);
    ~ComptabiliteForm();

private:
    Ui::ComptabiliteForm *ui;
};

#endif // COMPTABILITEFORM_H
