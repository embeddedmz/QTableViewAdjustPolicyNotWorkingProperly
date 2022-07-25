#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::printf("Qt Version : %s\n", QT_VERSION_STR);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
