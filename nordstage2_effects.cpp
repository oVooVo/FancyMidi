#include <nordstage2.h>
#include <qmath.h>

void NordStage2::stopEffects()
{
    _timer->stop();
}

void NordStage2::sineWaveDrawbar(int speed, int freq, int intervall) {

    connect(_timer, &QTimer::timeout, [this, speed, freq]() {
        for (int i = 1; i <= 9; i++) {
            double arg = speed * _time + i * 128/9.0;
            arg /= 128.0 * M_1_PI;
            arg *= freq;
            setOrganDrawBar(i, 64 * (1+qSin(arg)));
        }
        _time++;
    });
    _timer->start(intervall);
}
