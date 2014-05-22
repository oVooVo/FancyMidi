#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include "midiinputhandler.h"

class Keyboard : public QObject
{
    Q_OBJECT
public:
    Keyboard(quint8 channel = 0, QObject* parent = 0);
    quint8 channel() const { return _channel; }

public slots:
    void setChannel(quint8 channel);

private:
    quint8 _channel = 0;
    const MidiInputHandler* midi;

public:
    void sendMidiControlCommand(quint8 data1, quint8 data2);

};

#endif // KEYBOARD_H
