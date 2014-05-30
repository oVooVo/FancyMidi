#include "datainputport.h"
#include "dataoutputport.h"
#include <QDebug>

DataInputPort::DataInputPort(Node* node, QString name, QString tooltip) : InputPort(node, name, tooltip, Port::Data)
{
}

QVariant DataInputPort::data() const
{
    if (!source()) {
        return QVariant();
    }

    Q_ASSERT(source()->type() == Data);
    return ((DataOutputPort*) source())->data();
}

bool DataInputPort::hasData(QVariant &data) const
{
    data = this->data();
    return data.isValid();
}

void DataInputPort::notify(const QVariant &data) const
{
    node()->notify(this, data);
}
