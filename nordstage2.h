#ifndef NORDSTAGE2GEN_H
#define NORDSTAGE2GEN_H

#include <QMap>
#include <QString>
#include "Domain/domains.h"
#include "Domain/domain.h"
#include "keyboard.h"

class NordStage2 : public Keyboard
{
    NordStage2(int channel = 0, QObject *parent = 0);
public:
    ~NordStage2();
    Domain* getDomain(QString key);
    static QStringList getKeys();
    QMap<quint8, Domain*> domains() const { return _domains; }

private:
    QMap<quint8, Domain*> _domains;

private:
    struct Triple {
        Triple(QMap<QString, quint8> codes, QMap<quint8, QString> names, QMap<quint8, Domain*> domains) {
            this->codes = codes;
            this->names = names;
            this->domains = domains;
        }
        QMap<QString, quint8> codes;
        QMap<quint8, QString> names;
        QMap<quint8, Domain*> domains;
    } typedef Triple;
    static Triple createProperties();
    static NordStage2* CHANNELS[16];

public:
    static const QMap<QString, quint8> CODES;
    static const QMap<quint8, QString> NAMES;
    static const QMap<quint8, Domain*> DOMAINS;
    static const QMap<QString, QStringList> PROPERTIES;
    static QMap<QString,QStringList> calculateProperties();

    static NordStage2* channel(int i);
};

#endif // NORDSTAGE2GEN_H
