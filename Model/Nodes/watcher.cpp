#include "watcher.h"
#include "../datainputport.h"
#include "../triggeroutputport.h"

REGISTER_DEFN_NODETYPE(Watcher);

Watcher::Watcher(QDataStream& stream) : Node(stream)
{
    setName("Watcher");
    addPort(new DataInputPort(this, "Watched", ""));
    addPort(new TriggerOutputPort(this, "Value changed", ""));

}

void Watcher::notify(const DataInputPort *in, const QVariant &)
{
    if (in == dataInputPort("Watched")) {
        qDebug() << "trigger output";
        triggerOutputPort("Value changed")->trigger();
    }
}
