#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("pedrolcl");
    QCoreApplication::setOrganizationDomain("pedrolcl.github.io");
    QCoreApplication::setApplicationName(QT_STRINGIFY(PROGRAM));
    QCoreApplication::setApplicationVersion(QT_STRINGIFY(VERSION));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
