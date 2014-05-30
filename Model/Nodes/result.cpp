#include "result.h"
#include "../triggerinputport.h"
#include "../datainputport.h"
#include "logger.h"
#include "Settings/infosetting.h"

REGISTER_DEFN_NODETYPE(Result);

Result::Result(QDataStream& stream) : Node(stream)
{
    addPort(new TriggerInputPort(this, "Update", ""));
    addPort(new DataInputPort(this, "Data", ""));
    addSetting(new InfoSetting(this, "Info", "", ""));
}

void Result::trigger(const TriggerInputPort *port)
{
    Q_ASSERT(port == triggerInputPort("Update"));
    setting<InfoSetting>("Info")->setString(dataInputPort("Data")->data().toString());
}

void Result::notify(const DataInputPort *port, const QVariant &data)
{
    Q_ASSERT(port == dataInputPort("Data"));
    setting<InfoSetting>("Info")->setString(data.toString());
}
