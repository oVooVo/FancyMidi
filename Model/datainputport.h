#ifndef DATAINPUTPORT_H
#define DATAINPUTPORT_H

#include "inputport.h"

class DataInputPort : public InputPort
{
    Q_OBJECT
public:
    DataInputPort(Node *node, QString name, QString tooltip);

    QVariant data() const;
    bool hasData(QVariant& data) const;

    // is called when source port has new data
    void notify(const QVariant& data);

    void setFallback(QVariant fallback);
    QVariant fallback() const { return _fallback; }

signals:
    void dataChanged(const QVariant& data);   // this is only to update settings!

private:
    QVariant _fallback;
};

#endif // DATAINPUTPORT_H
