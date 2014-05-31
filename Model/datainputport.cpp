#include "datainputport.h"
#include "dataoutputport.h"
#include <QDebug>

DataInputPort::DataInputPort(Node* node, QString name, QString tooltip, bool canNotify)
    : InputPort(node, name, tooltip, Port::Data, canNotify)
{
}

QVariant DataInputPort::data() const
{
    if (!source()) {
        return _fallback;
    }

    Q_ASSERT(source()->type() == Data);

    return ((DataOutputPort*) source())->data();
}

bool DataInputPort::hasData(QVariant &data) const
{
    data = this->data();
    return data.isValid();
}

void DataInputPort::notify(const QVariant &data)
{
    if (notifies())
        node()->notify(this, data);

    // notify settings
    emit dataChanged(data);
    emit blink();
}

void DataInputPort::setFallback(QVariant fallback)
{
    if (_fallback == fallback)
        return;

    _fallback = fallback;
    notify(_fallback);
}

void DataInputPort::on_connect(Port *port)
{
    Q_ASSERT(port->type() == Data && !port->isInput());
    DataOutputPort* input = (DataOutputPort*) port;

    notify(input->data());
}
