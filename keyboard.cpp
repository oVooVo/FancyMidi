#include "keyboard.h"
#include <QDebug>

Keyboard::Keyboard(QObject *parent) : QObject(parent)
{
    midi = MidiInputHandler::singleton();
}

void Keyboard::setChannel(quint8 channel)
{
    if (channel > 15) {
        qWarning() << "expected channel to be between 0 and 15 but was " << channel;
        channel = 0;
    }
    _channel = channel;
}
