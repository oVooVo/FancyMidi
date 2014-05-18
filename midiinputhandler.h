#ifndef MIDIINPUTHANDLER_H
#define MIDIINPUTHANDLER_H

#include <QString>
#include <QSocketNotifier>
#include <QObject>
#include <QFile>
#include <QEvent>

class MidiInputHandler : public QObject
{
    Q_OBJECT
private:
    MidiInputHandler();
public:
    enum MidiType { NoteOn, NoteOff, ControlChange, ProgramChange, PitchBend, Aftertouch, Unknown};

private:
    QSocketNotifier* _notifier = 0;
    bool _valid = false;
    static quint8 getChannel(quint8 code);
    static MidiInputHandler::MidiType getType(quint8 code);
    static quint8 statusByte(MidiInputHandler::MidiType type, quint8 channel);
    bool _verbose = true;
    bool connectMidiDevice_Private();
    bool disconnectMidiDevice_Private();

private slots:
    void readyRead();

signals:
    void receivedMidiCommand(MidiType type, quint8 channel, quint8 data1, quint8 data2);
public slots:
    void sendMidiCommand(MidiType type, quint8 channel, quint8 data1, quint8 data2) const;
    void sendMidiControlCommand(quint8 channel, quint8 data1, quint8 data2) const;



    // Singleton administration
public:
    static const MidiInputHandler* singleton();
    static bool disconnectMidiDevice() { return _singleton->disconnectMidiDevice_Private(); }
    static bool connectMidiDevice() { return _singleton->connectMidiDevice_Private(); }
    static bool valid() { return singleton()->_valid; }
    static QString typeToString(MidiType type);
private:
    static MidiInputHandler* _singleton;
};

#endif // MIDIINPUTHANDLER_H
