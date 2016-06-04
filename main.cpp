#include "mainwindow.h"
#include "board.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   // w.show();

    Board b;
    b.show();
    return a.exec();
}
