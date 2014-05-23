#include "midicommandselectsetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>
#include "nordstage2.h"

MidiCommandSelectSetting::MidiCommandSelectSetting(Node *parent, QString name, QString tooltip):
    Setting(parent, name, tooltip)
{
    Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(),
               "constructor", "called from a thread other than the main thread");
    _currentCategory = 0;

    connect(parent, SIGNAL(channelChanged(int)), this, SIGNAL(changed()));
    setValid(true);
}

MidiCommandSelectSetting::~MidiCommandSelectSetting()
{
    Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(),
               "destructor", "called from a thread other than the main thread");
}

QDataStream &operator<<(QDataStream &out, const MidiCommandSelectSetting *selectSetting)
{
    return out;
}

QDataStream &operator>>(QDataStream &in, MidiCommandSelectSetting *&setting)
{
    return in;
}

void MidiCommandSelectSetting::setDouble(double d)
{
    Q_ASSERT(domainType() == Domain::Double);
    if (qFuzzyCompare(((DoubleDomain*) domain())->value(), d)) return;

    ((DoubleDomain*) domain())->setValue(d);
    emitChanged();
}

void MidiCommandSelectSetting::setInt(int i)
{
    Q_ASSERT(domainType() == Domain::Integer);
    if (((IntegerDomain*) domain())->value() == i) return;

    ((IntegerDomain*) domain())->setValue(i);
    emitChanged();
}

void MidiCommandSelectSetting::setIndex(int i)
{
    Q_ASSERT(domainType() == Domain::Discrete);
    if (((DiscreteDomain*) domain())->index() == i) return;

    ((DiscreteDomain*) domain())->setIndex(i);
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
    if (i == _currentCategory)
        return;

    _currentCategory = qBound(0, i, NordStage2::categories().length() - 1);
    _currentProperty = 0;

    emitChanged();
}

void MidiCommandSelectSetting::setPropertyIndex(int i)
{
    if (i == _currentProperty)
        return;

    _currentProperty = qBound(0, i, NordStage2::properties(_currentCategory).length() - 1);
    emitChanged();
}

void MidiCommandSelectSetting::setChannel(int i)
{
    if (i == _currentChannel)
        return;

    _currentChannel = qBound(0, i, 15);
    emit changed();
}


MidiKey MidiCommandSelectSetting::midiKey() const
{
    Q_ASSERT(NordStage2::CODES.contains(key()));

    return NordStage2::CODES[key()];

}

Domain* MidiCommandSelectSetting::domain() const
{
    return NordStage2::channel(channel())->domains()[midiKey()];
}

Domain::Type MidiCommandSelectSetting::domainType() const
{
    return domain()->type();
}

double MidiCommandSelectSetting::value() const
{
    Q_ASSERT(domainType() == Domain::Double || domainType() == Domain::Integer);

    switch (domainType()) {
    case Domain::Double:
        return ((DoubleDomain*) domain())->value();
    case Domain::Integer:
        return ((IntegerDomain*) domain())->value();
    default:
        return 0;
    }
}

int MidiCommandSelectSetting::index() const
{
    Q_ASSERT(domainType() == Domain::Discrete);

    return ((DiscreteDomain*) domain())->index();
}
