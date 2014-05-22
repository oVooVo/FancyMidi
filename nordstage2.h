#ifndef NORDSTAGE2GEN_H
#define NORDSTAGE2GEN_H

#include <QMap>
#include <QString>
#include "Domain/domains.h"
#include "Domain/domain.h"
#include "keyboard.h"

class NordStage2 : public Keyboard
{
public:
    NordStage2(int channel = 0, QObject *parent = 0);
    ~NordStage2();
    Domain* getDomain(QString key);
    static QStringList getKeys();

private:
    QMap<quint8, Domain*> _domains;

private:
    struct Triple {
        Triple(QMap<QString, quint8> codes, QMap<quint8, QString> properties, QMap<quint8, Domain*> domains) {
            this->codes = codes;
            this->properties = properties;
            this->domains = domains;
        }
        QMap<QString, quint8> codes;
        QMap<quint8, QString> properties;
        QMap<quint8, Domain*> domains;
    } typedef Triple;
    static Triple createProperties();

public:
    static const QMap<QString, quint8> CODES;
    static const QMap<quint8, QString> PROPERTIES;
    static const QMap<quint8, Domain*> DOMAINS;
};

#endif // NORDSTAGE2GEN_H
