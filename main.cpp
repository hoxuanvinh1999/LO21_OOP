#include <QApplication>
#include "gui/MainWindow.h"
#include "core/Transaction.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow main;
    main.show();
    return app.exec();
}
