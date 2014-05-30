#ifndef DATAOUTPUTPORT_H
#define DATAOUTPUTPORT_H

#include "outputport.h"


class DataOutputPort : public OutputPort
{
public:
    DataOutputPort(Node *node, QString name, QString tooltip);

    QVariant data() const;
    bool hasData(QVariant& data) const;

public slots:
    void setData(QVariant data);
    void clearData() { _data = QVariant(); }

private:
    QVariant _data;
};

#endif // DATAOUTPUTPORT_H
