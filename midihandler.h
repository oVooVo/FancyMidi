#ifndef MidiHandler_H
#define MidiHandler_H

#include <QString>
#include <QSocketNotifier>
#include <QObject>
#include <QFile>
#include <QEvent>
#include "midikey.h"

class MidiHandler : public QObject
{
    Q_OBJECT
private:
    MidiHandler();
public:

private:
    QSocketNotifier* _notifier = 0;
    bool _valid = false;
    static int getChannel(quint8 code);
    static MidiKey::MidiType getType(quint8 code);
    static quint8 statusByte(MidiKey::MidiType type, quint8 channel);
    bool connectMidiDevice_Private();
    bool disconnectMidiDevice_Private();

private slots:
    void readyRead();

signals:
    void receivedMidiCommand(MidiKey key, int channel, quint8 data2);
public slots:
    void sendMidiCommand(MidiKey key, quint8 channel, quint8 data2) const;


    // Singleton administration
public:
    static const MidiHandler* singleton();
    static bool disconnectMidiDevice() { return _singleton->disconnectMidiDevice_Private(); }
    static bool connectMidiDevice() { return _singleton->connectMidiDevice_Private(); }
    static bool valid() { return singleton()->_valid; }
    static QString typeToString(MidiKey::MidiType type);
private:
    static MidiHandler* _singleton;
};

#endif // MidiHandler_H
