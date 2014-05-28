#include "sequencesetting.h"

REGISTER_DEFN_SETTINGTYPE(SequenceSetting);

const QString SequenceSetting::FLAT =  QString("♭");
const QString SequenceSetting::SHARP = QString("♯");
const QString SequenceSetting::OCTAVE_UP   = QString("'");
const QString SequenceSetting::OCTAVE_DOWN = QString(",");

SequenceSetting::SequenceSetting(QDataStream& stream) : Setting(stream)
{
    QString sequence;
    stream >> sequence;
    setSequence(sequence);
}

void SequenceSetting::writeToStream(QDataStream &stream) const
{
    Setting::writeToStream(stream);
    stream << _sequence;
}

SequenceSetting::SequenceSetting(Node *parent, QString name, QString infoText, bool showInNode)
    : Setting(parent, name, infoText, showInNode)
{

}

bool SequenceSetting::setSequence(QString seq)
{
    if (seq == _sequence)
        return _valid;

    _sequence = seq;
    seq.replace(QRegExp("\\s+"), "");
    auto take = [](QString& string, QString& actualToken, QRegExp token)
    {
        QString oldString = string;
        string.remove(token);
        actualToken = oldString.left(oldString.length() - string.length());
        return !actualToken.isEmpty();
    };

    auto noteValue = [](QString note) {
        if (note == "C")
            return 60;
        if (note == "D")
            return 62;
        if (note == "E")
            return 64;
        if (note == "F")
            return 65;
        if (note == "G")
            return 67;
        if (note == "A")
            return 69;
        if (note == "H" || note == "B")
            return 71;
        return 0;
    };

    auto decode = [](int note, int accidental, int octave)
    {
        return note + 12 * octave + accidental;
    };

    _notes.clear();

    _valid = true;
    while (!seq.isEmpty()) {
        QString note, accidental, octave;
        if (!take(seq, note, QRegExp("^[A-H]"))) {
            _valid = false;
            break;
        }
        take(seq, accidental, QRegExp(QString("^(%1|%2)").arg(FLAT, SHARP)));
        take(seq, octave, QRegExp(QString("^(%1+|%2+)").arg(OCTAVE_UP).arg(OCTAVE_DOWN)));
        _notes.append(decode(noteValue(note),
                             accidental.isEmpty() ? 0 : accidental == FLAT ? -1 : 1,
                             (octave.startsWith(OCTAVE_UP) ? -1 : 1) * octave.length()));
        qDebug() << "set value " << _notes.last();
    }

    emit changed();
    return _valid;
}

int SequenceSetting::note(int key) const
{
    return contains(key) ? _notes[key] : 0;
}
