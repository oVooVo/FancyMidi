#ifndef NORDSTAGE2GEN_H
#define NORDSTAGE2GEN_H

#include <QMap>
#include <QString>
#include "Domain/domains.h"
#include "Domain/domain.h"
#include "keyboard.h"

class NordStage2 : public Keyboard
{
    Q_OBJECT
    NordStage2(int channel = 0, QObject *parent = 0);
public:
    ~NordStage2();
    Domain* getDomain(QString key);
    static QStringList getKeys();
    QMap<MidiKey, Domain*> domains() const { return _domains; }

private:
    QMap<MidiKey, Domain*> _domains;

private:
    struct Triple {
        Triple(QMap<QString, MidiKey> codes, QMap<MidiKey, QString> names, QMap<MidiKey, Domain*> domains) {
            this->codes = codes;
            this->names = names;
            this->domains = domains;
        }
        QMap<QString, MidiKey> codes;
        QMap<MidiKey, QString> names;
        QMap<MidiKey, Domain*> domains;
    } typedef Triple;
    static Triple createProperties();
    static NordStage2* CHANNELS[16];

public:
    static const QMap<QString, MidiKey> CODES;
    static const QMap<MidiKey, QString> NAMES;
    static const QMap<MidiKey, Domain*> DOMAINS;
    static const QMap<QString, QStringList> PROPERTIES;
    static QMap<QString,QStringList> calculateProperties();

    static NordStage2* channel(int i);
    static QStringList categories();
    static QStringList properties(int category);
    static int propertyIndex(MidiKey key);
    static int categoryIndex(MidiKey key);


private:
    void installReceiver(int myChannel);

signals:
    void midiInput(int channel, MidiKey key, QVariant value);

};

#endif // NORDSTAGE2GEN_H
