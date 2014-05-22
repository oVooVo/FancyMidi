#include "keyboardnode.h"
#include "../simpleinputport.h"
#include <QDebug>


KeyboardNode::KeyboardNode(QPoint position, Project *parent, QString name, QString infoText, QSizeF size) :
    Node(position, parent, name, infoText, size)
{
    _inputs += new SimpleInputPort(this, "set value", "secret text");
    polish();
}
