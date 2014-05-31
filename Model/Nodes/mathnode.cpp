#include "mathnode.h"
#include "Settings/doublesetting.h"
#include "Settings/selectsetting.h"
#include <QDebug>
#include "../datainputport.h"
#include "../dataoutputport.h"
#include <qmath.h>

REGISTER_DEFN_NODETYPE(MathNode);

#define GEQ "≥"
#define LEQ "≤"
#define NEQ "≠"
#define IMP "⇒"
#define AND "∧"
#define OR "∨"
#define NOT "¬"

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
                                 << "+" << "-" << "*" << "/" << "%" << "^"
                                 << "<" << LEQ << ">" << GEQ << "=" << NEQ
                                 << AND << OR  << NOT << IMP
                                 << "own",
                                 0));

    setting<DoubleSetting>("A")->connectPort(dataInputPort("A"));
    setting<DoubleSetting>("B")->connectPort(dataInputPort("B"));

    connect(setting<SelectSetting>("Operator"), &Setting::changed, [this](){
        // disable "B" when operator = "NOT"
        setting<DoubleSetting>("B")->setEnabled(setting<SelectSetting>("Operator")->value() != 14);

        calculate();
    });


}

void MathNode::notify(const DataInputPort *in, const QVariant &)
{
    if (in == dataInputPort("A") || in == dataInputPort("B")) {
        calculate();
    }
}

void MathNode::calculate() const
{
    double a = dataInputPort("A")->data().value<double>();
    double b = dataInputPort("B")->data().value<double>();
    bool bool_a = dataInputPort("A")->data().value<bool>();
    bool bool_b = dataInputPort("B")->data().value<bool>();

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
        a = fmod(a, b);
        if (a < 0)
            a += b;
        dataOutputPort("Result")->setData(a);
        break;
    case 5:
        dataOutputPort("Result")->setData(qPow(a, b));
        break;
    case 6:
        dataOutputPort("Result")->setData(a < b);
        break;
    case 7:
        dataOutputPort("Result")->setData(a <= b);
        break;
    case 8:
        dataOutputPort("Result")->setData(a > b);
        break;
    case 9:
        dataOutputPort("Result")->setData(a >= b);
        break;
    case 10:
        dataOutputPort("Result")->setData(qFuzzyCompare(a, b));
        break;
    case 11:
        dataOutputPort("Result")->setData(!qFuzzyCompare(a, b));
        break;
    case 12:
        dataOutputPort("Result")->setData(bool_a & bool_b);
        break;
    case 13:
        dataOutputPort("Result")->setData(bool_a | bool_b);
        break;
    case 14:
        dataOutputPort("Result")->setData(!bool_a);
        break;
    case 15:
        dataOutputPort("Result")->setData(!bool_a | bool_b);
        break;
    case 16:
        dataOutputPort("Result")->setData(/*//TODO parse(term, a, b)*/ 0);
        break;
    }
}
