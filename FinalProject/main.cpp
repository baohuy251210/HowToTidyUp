#include "mainwindow.h"

#include <QApplication>


#include "Box2D/Box2D.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1024,768);
    w.show();
    return a.exec();

}
