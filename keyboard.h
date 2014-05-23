#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include "midihandler.h"

class Keyboard : public QObject
{
    Q_OBJECT
public:
    Keyboard(quint8 channel = 0, QObject* parent = 0);
    quint8 channel() const { return _channel; }

public slots:
    void setChannel(quint8 channel);

    void sendMidiCommand(MidiKey key, quint8 data);

private:
    quint8 _channel = 0;
    const MidiHandler* midi;
};

#endif // KEYBOARD_H
