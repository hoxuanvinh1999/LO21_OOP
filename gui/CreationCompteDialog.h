#ifndef CREATIONCOMPTEDIALOG_H
#define CREATIONCOMPTEDIALOG_H

#include <QDialog>

namespace Ui {
    class CreationCompteDialog;
}

class CreationCompteDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreationCompteDialog(QWidget *parent = nullptr);
    ~CreationCompteDialog();

private:
    Ui::CreationCompteDialog *ui;
};

#endif // CREATIONCOMPTEDIALOG_H
