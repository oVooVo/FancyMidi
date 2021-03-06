#include "midicommandselectsetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>
#include "nordstage2.h"
#include "Model/datainputport.h"

//TODO MidiCommandSelectSetting needs midi channel inside.

REGISTER_DEFN_SETTINGTYPE(MidiCommandSelectSetting);

MidiCommandSelectSetting::MidiCommandSelectSetting(Node *parent, QString name, QString tooltip,
                                                   bool showInNode)
    : Setting(parent, name, tooltip, showInNode)
{
    Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(),
               "constructor", "called from a thread other than the main thread");
    _currentCategory = 0;
    updateDomain();
}

MidiCommandSelectSetting::MidiCommandSelectSetting(QDataStream &stream)
    : Setting(stream)
{
    stream >> _currentCategory >> _currentProperty >> _value;
    updateDomain();
}

void MidiCommandSelectSetting::writeToStream(QDataStream &stream) const
{
    Setting::writeToStream(stream);
    stream << _currentCategory << _currentProperty << _value;
}

void MidiCommandSelectSetting::updateDomain()
{
    if (_domain) {
        delete _domain;
    }
    _domain = NordStage2::DOMAINS[midiKey()]->copy(NordStage2::channel(0));
    setValue(_value);
}



MidiCommandSelectSetting::~MidiCommandSelectSetting()
{
    Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(),
               "destructor", "called from a thread other than the main thread");
}

void MidiCommandSelectSetting::setValue(QVariant v)
{
    _value = v;
    switch (domain()->type()) {
    case Domain::Discrete:
        ((DiscreteDomain*) domain())->setIndex(v.value<int>());
        break;
    case Domain::Integer:
        ((IntegerDomain*) domain())->setValue(v.value<int>());
        break;
    case Domain::Double:
        ((DoubleDomain*) domain())->setValue(v.value<double>());
        break;
    }

    emitChanged();
}

double MidiCommandSelectSetting::min() const
{
    Q_ASSERT(domainType() == Domain::Double || domainType() == Domain::Integer);

    switch (domainType()) {
    case Domain::Double:
        return ((DoubleDomain*) domain())->min();
    case Domain::Integer:
        return ((IntegerDomain*) domain())->min();
    default:
        return 0;
    }
}

double MidiCommandSelectSetting::max() const
{
    Q_ASSERT(domainType() == Domain::Double || domainType() == Domain::Integer);

    switch (domainType()) {
    case Domain::Double:
        return ((DoubleDomain*) domain())->max();
    case Domain::Integer:
        return ((IntegerDomain*) domain())->max();
    default:
        return 0;
    }
}

QStringList MidiCommandSelectSetting::items() const
{
    Q_ASSERT(domainType() == Domain::Discrete);

    return ((DiscreteDomain*) domain())->values();
}

void MidiCommandSelectSetting::setCategoryIndex(int i)
{
    _currentCategory = qBound(0, i, NordStage2::categories().length() - 1);
    _currentProperty = qBound(0, _currentProperty, NordStage2::properties(_currentCategory).length() - 1);

    updateDomain();
    emitChanged();
}

void MidiCommandSelectSetting::setPropertyIndex(int i)
{
    _currentProperty = qBound(0, i, NordStage2::properties(_currentCategory).length() - 1);
    updateDomain();
    emitChanged();
}


MidiKey MidiCommandSelectSetting::midiKey() const
{
    Q_ASSERT(NordStage2::CODES.contains(key()));

    return NordStage2::CODES[key()];

}

Domain::Type MidiCommandSelectSetting::domainType() const
{
    return domain()->type();
}

double MidiCommandSelectSetting::value() const
{
    switch (domainType()) {
    case Domain::Double:
        return ((DoubleDomain*) domain())->value();
    case Domain::Integer:
        return ((IntegerDomain*) domain())->value();
    case Domain::Discrete:
        return ((DiscreteDomain*) domain())->index();
    default:
        return 0;
    }
}

int MidiCommandSelectSetting::index() const
{
    Q_ASSERT(domainType() == Domain::Discrete);

    return ((DiscreteDomain*) domain())->index();
}

void MidiCommandSelectSetting::connectPort(DataInputPort *category, DataInputPort *property, DataInputPort *value)
{
    category->setFallback(_currentCategory);
    property->setFallback(_currentProperty);
    value->setFallback(_value);

    connect(this, &Setting::changed, [category, property, value, this]() {
        category->setFallback(_currentCategory);
        property->setFallback(_currentProperty);
        value->setFallback(_value);
    });

    connect(category, &DataInputPort::dataChanged, [this, category]() {
        setCategoryIndex(category->data().value<int>());
    });
    connect(property, &DataInputPort::dataChanged, [this, property]() {
        setPropertyIndex(property->data().value<int>());
    });
    connect(value, &DataInputPort::dataChanged, [this, value]() {
        setValue(value->data());
    });

    connect(category, &DataInputPort::connectionToggled, [this](bool connected) {
        setCategoryEnabled(!connected);
    });
    connect(property, &DataInputPort::connectionToggled, [this](bool connected) {
        setPropertyEnabled(!connected);
    });
    connect(value, &DataInputPort::connectionToggled, [this](bool connected) {
        setValueEnabled(!connected);
    });
}


void MidiCommandSelectSetting::setCategoryEnabled(bool enabled)
{
    if (_categoryEnabled == enabled)
        return;

    _categoryEnabled = enabled;
    emit categoryEnabledChanged(enabled);
}

void MidiCommandSelectSetting::setPropertyEnabled(bool enabled)
{

    if (_propertyEnabled == enabled)
        return;

    _propertyEnabled = enabled;
    emit propertyEnabledChanged(enabled);
}

void MidiCommandSelectSetting::setValueEnabled(bool enabled)
{

    if (_valueEnabled == enabled)
        return;

    _valueEnabled = enabled;
    emit valueEnabledChanged(enabled);
}

Domain* MidiCommandSelectSetting::domain() const
{
    return _domain;
}






























