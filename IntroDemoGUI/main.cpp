#include "mainwindow.h"

#include <QApplication>

#include <SFML/System.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
