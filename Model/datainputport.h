#ifndef DATAINPUTPORT_H
#define DATAINPUTPORT_H

#include "inputport.h"

class DataInputPort : public InputPort
{
public:
    DataInputPort(Node *node, QString name, QString tooltip);

    QVariant data() const;
    bool hasData(QVariant& data) const;
    void notify(const QVariant& data) const;
};

#endif // DATAINPUTPORT_H
