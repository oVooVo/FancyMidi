#include <QApplication>
#include <QFile>
#include <QDebug>
#include "midiinputhandler.h"
#include "nordstage2.h"
#include <QTimer>
#include <qmath.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NordStage2* s2 = new NordStage2();
    s2->setReverbSize(NordStage2::Hall2);


    return a.exec();
}

#ifdef UNDEFINED    // find NordStage2::RateSamples
QString string;
int count = 0;
for (int f = 0; f <= 3; f++) {
    for (int i = 80; i <= 160; i+=2) {
        if (f == 0 && (i == 146 || i == 150 || i == 154 || i == 158)) continue;
        if (f == 1 && (i == 80 || i == 138 || i == 142 || i == 146
                       || i == 150 || i == 154 || i == 158)) continue;
        if (f == 2 && (i == 80 || i == 134 || i == 138 || i == 142
                       || i == 146 || i == 150 || i == 154
                       || i == 158)) continue;
        if (f == 3 && i == 80) continue;
        if (f == 3 && i > 128) break;
        string += QString("%1,").arg(i * qPow(2, f));
        count++;
    }
}
qDebug() << string;
#endif
