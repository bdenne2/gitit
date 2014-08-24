#include <QtGui/QApplication>
#include "mainwindow.h"

///@mainpage Gitit
///@version alpha
///@author Stephen Sennebogan, Bryanna Denney, Michael Salata

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("gitit");
    a.setOrganizationName("BMH Software");
    MainWindow w;
    w.show();

    return a.exec();
}
