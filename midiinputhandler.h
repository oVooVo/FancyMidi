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
    bool valid() const { return _valid; }

private:
    QSocketNotifier* _notifier = 0;
    bool _valid = false;
    static quint8 getChannel(quint8 code);
    static MidiInputHandler::MidiType getType(quint8 code);

private slots:
    void readyRead();

signals:
    void receivedMidiCommand(MidiInputHandler::MidiType type, quint8 channel, quint8 data1, quint8 data2);



    // Singleton administration
public:
    static const MidiInputHandler* singleton();
private:
    static MidiInputHandler* _singleton;
};

#endif // MIDIINPUTHANDLER_H
