#include "triggernode.h"
#include "../outputport.h"
#include <QTimer>
#include <QDebug>

REGISTER_DEFN_NODETYPE(TriggerNode);

TriggerNode::TriggerNode(QPoint position, Project* parent) : Node(position, parent, "Trigger")
{

    timer.start(200);
    connect(&timer, &QTimer::timeout, [this]() {
        qDebug() << "targets:" << _outputs[0]->_targets;
    });
    _outputs += new OutputPort(this, "", "Trigger", Port::Trigger);
}
