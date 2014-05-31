#include <QApplication>
#include <QFile>
#include <QDebug>
#include "midihandler.h"
#include "nordstage2.h"
#include <QTimer>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("FancyMidi");
    QApplication::setOrganizationName("Me");

    MainWindow m;
    m.show();

    return a.exec();
}
