#include "nordstage2.h"
#include <QDebug>


NordStage2::NordStage2()
{
    _timer = new QTimer(this);
}

quint8 NordStage2::encodeOctaveShift(int shift)
{
    if (shift < -7 || shift >= 7) {
        qWarning() << "Expected octave shift between -7 and 6 but got " << shift << ".";
    }
    quint8 value = 10 * (shift + 7);
    if (value > 40)  value -= 1;
    if (value > 80)  value -= 1;
    if (value > 120) value -= 1;

    return value;
}


