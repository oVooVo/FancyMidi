#ifndef SEQUENCESETTING_H
#define SEQUENCESETTING_H

#include "setting.h"
#include <QDataStream>

class SequenceSetting : public Setting
{
    Q_OBJECT
public:
    SequenceSetting(Node* parent, QString name, QString infoText, bool showInNode = true);
    SequenceSetting(QDataStream &stream);
    void writeToStream(QDataStream &stream) const;

    bool contains(int key) const { return key < _notes.size(); }
    int note(int key) const;
    bool setSequence(QString seq);
    QString sequence() const { return _sequence; }
    bool valid() const { return _valid; }

    static const QString FLAT;
    static const QString SHARP;
    static const QString OCTAVE_UP;
    static const QString OCTAVE_DOWN;

private:
    QList<int> _notes;
    QString _sequence;
    bool _valid = false;
    REGISTER_DECL_SETTINGTYPE(SequenceSetting);
};

#endif // SEQUENCESETTING_H
