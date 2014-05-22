#include <QApplication>
#include <QFile>
#include <QDebug>
#include "midiinputhandler.h"
#include "nordstage2.h"
#include <QTimer>

enum Test { A = 0, B = 1 };

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NordStage2* ns2 = new NordStage2();
    //qDebug() << NordStage2Gen::CODES;

    qDebug() <<((DoubleDomain*) ns2->getDomain("Organ Level"))->min();
    qDebug() <<((DoubleDomain*) ns2->getDomain("Organ Level"))->max();
    ((DoubleDomain*) ns2->getDomain("Organ Level"))->setValue(0.5);



    return a.exec();
}
