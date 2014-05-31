#ifndef TRIGGERINPUTPORT_H
#define TRIGGERINPUTPORT_H

#include "inputport.h"

class TriggerInputPort : public InputPort
{
public:
    TriggerInputPort(Node* node, QString name, QString tooltip);

    void trigger();
};

#endif // TRIGGERINPUTPORT_H
