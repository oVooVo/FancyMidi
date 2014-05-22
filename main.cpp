#include <QApplication>
#include <QFile>
#include <QDebug>
#include "midiinputhandler.h"
#include "nordstage2.h"
#include <QTimer>
#include "mainwindow.h"

enum Test { A = 0, B = 1 };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow m;
    m.show();


    return a.exec();
}
