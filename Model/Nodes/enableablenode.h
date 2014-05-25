#ifndef ENABLEABLENODE_H
#define ENABLEABLENODE_H

#include "../node.h"
#include "Settings/boolsetting.h"

class EnableableNode : public Node
{
public:
    EnableableNode(QPoint point, Project* parent, QString name, QString infotext = "");

};

#endif // ENABLEABLENODE_H
