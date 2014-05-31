#include "dataoutputport.h"
#include "Nodes/node.h"
#include <QDebug>
#include "datainputport.h"
#include "triggerinputport.h"

DataOutputPort::DataOutputPort(Node* node, QString name, QString tooltip) : OutputPort(node, name, tooltip, Port::Data)
{
}

void DataOutputPort::setData(QVariant data)
{
    if (_data == data)
        return;

    _data = data;
    for (InputPort* in : targets()) {
        if (in->type() == Data)
            ((DataInputPort*) in)->notify(data);
        else
            ((TriggerInputPort*) in)->trigger();
    }
    emit blink();
}

bool DataOutputPort::hasData(QVariant& data) const
{
    data = _data;
    return data.isValid();
}

QVariant DataOutputPort::data() const
{
    return _data;
}
