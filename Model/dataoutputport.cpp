#include "dataoutputport.h"
#include "Nodes/node.h"
#include <QDebug>
#include "datainputport.h"

DataOutputPort::DataOutputPort(Node* node, QString name, QString tooltip) : OutputPort(node, name, tooltip, Port::Data)
{
}

void DataOutputPort::setData(QVariant data)
{
    _data = data;
    for (InputPort* in : targets()) {
        Q_ASSERT(in->type() == Data);
        ((DataInputPort*) in)->notify(data);
    }
}

bool DataOutputPort::hasData(QVariant& data) const
{
    data = _data;
    return data.isValid();
}

QVariant DataOutputPort::data() const
{
    node()->updateData(this);
    return _data;
}
