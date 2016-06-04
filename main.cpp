#include "mainwindow.h"
#include <QApplication>


#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   // w.show();

    Controller c;
    c.show();
    return a.exec();
}
