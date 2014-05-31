#ifndef TRIGGEROUTPUTPORT_H
#define TRIGGEROUTPUTPORT_H

#include "outputport.h"

class TriggerOutputPort : public OutputPort
{
public:
    TriggerOutputPort(Node *node, QString name, QString tooltip);
    void trigger();

};

#endif // TRIGGEROUTPUTPORT_H
