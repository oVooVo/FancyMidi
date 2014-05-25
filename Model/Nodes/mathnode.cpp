#include "mathnode.h"
#include "Settings/doublesetting.h"
#include "Settings/selectsetting.h"
#include <QDebug>

REGISTER_DEFN_NODETYPE(MathNode);

MathNode::MathNode(QPoint position, Project *parent)
    : EnableableNode(position, parent, "Math")
{
    addPort(new InputPort(this, "A", "", Port::Scalar));
    addPort(new InputPort(this, "B", "", Port::Scalar));
    addPort(new OutputPort(this, "Result", "", Port::Scalar));

    addSetting(new DoubleSetting(this, "A", "", 0, 0));
    addSetting(new DoubleSetting(this, "B", "", 0, 0));

    addSetting(new SelectSetting(this, "Operator", "", 0, QStringList()
                                 << "+" << "-" << "*" << "/" << "own", 0));

    setting<DoubleSetting>("A")->connectPort(inputPort("A"));
    setting<DoubleSetting>("B")->connectPort(inputPort("B"));

    connect(setting<DoubleSetting>("A"), SIGNAL(changed()), this, SLOT(calculate()));
    connect(setting<DoubleSetting>("B"), SIGNAL(changed()), this, SLOT(calculate()));

}

void MathNode::calculate()
{
    double a = setting<DoubleSetting>("A")->value();
    double b = setting<DoubleSetting>("B")->value();
    double result;

    QMap<QString, double> map;
    map.insert("A", a);
    map.insert("B", b);

    switch (setting<SelectSetting>("Operator")->currentIndex()) {
    case 0:
        result = a + b;
        break;
    case 1:
        result = a - b;
        break;
    case 2:
        result = a * b;
        break;
    case 3:
        result = a / b;
        break;
    case 4:
        //TODO result = Parser::parse(setting<StringSetting>("term")->value(), map);
        result = 0;
        break;
    }

    outputPort("Result")->send(result);
}
