#include "mathnode.h"
#include "Settings/doublesetting.h"
#include "Settings/selectsetting.h"
#include <QDebug>
#include "../datainputport.h"
#include "../dataoutputport.h"

REGISTER_DEFN_NODETYPE(MathNode);

MathNode::MathNode(QDataStream& stream)
    : Node(stream)
{
    setName("Math");
    addPort(new DataInputPort(this, "A", ""));
    addPort(new DataInputPort(this, "B", ""));
    addPort(new DataOutputPort(this, "Result", ""));

    addSetting(new DoubleSetting(this, "A", "", 0, 0));
    addSetting(new DoubleSetting(this, "B", "", 0, 0));


    addSetting(new SelectSetting(this, "Operator", "", 0, QStringList()
                                 << "+" << "-" << "*" << "/" << "%" << "own", 0));


    setting<DoubleSetting>("A")->connectPort(dataInputPort("A"));
    setting<DoubleSetting>("B")->connectPort(dataInputPort("B"));
}

void MathNode::updateData(const DataOutputPort *port) const
{
    if (port == dataOutputPort("Result")) {
        calculate();
    } else {
        Q_ASSERT(false);
    }
}

void MathNode::notify(const DataInputPort *in, const QVariant &)
{
    if (in == dataInputPort("A") || in == dataInputPort("B")) {
        calculate();
    } else {
        UNKNOWN_PORT;
    }
}

void MathNode::calculate() const
{
    double a = dataInputPort("A")->data().value<double>();
    double b = dataInputPort("B")->data().value<double>();
    switch (setting<SelectSetting>("Operator")->value()) {
    case 0:
        dataOutputPort("Result")->setData(a + b);
        break;
    case 1:
        dataOutputPort("Result")->setData(a - b);
        break;
    case 2:
        dataOutputPort("Result")->setData(a * b);
        break;
    case 3:
        dataOutputPort("Result")->setData(a / b);
        break;
    case 4:
        dataOutputPort("Result")->setData(fmod(a, b));
        break;
    case 5:
        dataOutputPort("Result")->setData(/*//TODO parse(term, a, b)*/ 0);
        break;
    }
}
