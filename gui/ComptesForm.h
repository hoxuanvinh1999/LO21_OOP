#ifndef COMPTESFORM_H
#define COMPTESFORM_H

#include <QWidget>

namespace Ui {
    class ComptesForm;
}

class ComptesForm : public QWidget {
    Q_OBJECT

public:
    explicit ComptesForm(QWidget *parent = nullptr);
    ~ComptesForm();

private:
    Ui::ComptesForm *ui;
};

#endif // COMPTESFORM_H
