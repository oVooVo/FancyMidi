#ifndef KEYBOARDNODE_H
#define KEYBOARDNODE_H

#include "../node.h"

class KeyboardNode : public Node
{
public:
    KeyboardNode(QPoint position, Project *parent, QString name, QString infoText, QSizeF size);
};

#endif // KEYBOARDNODE_H
