#include <QApplication>
#include <QtWidgets>
#include "mainwindow.h"
#include "mapstar.h"
#include "solver.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
