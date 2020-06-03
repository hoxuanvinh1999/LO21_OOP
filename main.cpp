#include <QApplication>
#include "gui/MainWindow.h"
#include <QDebug>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow main;
    main.show();
    return app.exec();
}
