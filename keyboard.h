#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include "midiinputhandler.h"

class Keyboard : public QObject
{
    Q_OBJECT
public:
    Keyboard(QObject* parent = 0);
    quint8 channel() const { return _channel; }

public slots:
    void setChannel(quint8 channel);

private:
    quint8 _channel = 0;

protected:
    const MidiInputHandler* midi;

};

#endif // KEYBOARD_H
