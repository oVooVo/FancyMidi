#include "midicommandselectsetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>
#include "nordstage2.h"

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
    stream >> _currentCategory >> _currentProperty >> _currentChannel;
    updateDomain();
}

void MidiCommandSelectSetting::writeToStream(QDataStream &stream) const
{
    Setting::writeToStream(stream);
    stream << _currentCategory << _currentProperty << _currentChannel;
}

void MidiCommandSelectSetting::updateDomain()
{
    if (_domain)
        delete _domain;

    _domain = NordStage2::DOMAINS[midiKey()]->copy(NordStage2::channel(0));
}



MidiCommandSelectSetting::~MidiCommandSelectSetting()
{
    Q_ASSERT_X(QApplication::instance()->thread() == QThread::currentThread(),
               "destructor", "called from a thread other than the main thread");
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

    updateDomain();
    emitChanged();
}

void MidiCommandSelectSetting::setPropertyIndex(int i)
{
    if (i == _currentProperty)
        return;

    _currentProperty = qBound(0, i, NordStage2::properties(_currentCategory).length() - 1);

    updateDomain();
    emitChanged();
}

void MidiCommandSelectSetting::setChannel(int i)
{
    if (i == _currentChannel)
        return;

    updateDomain();
    _currentChannel = qBound(0, i, Keyboard::NUM_MIDI_CHANNELS - 1);
    emit changed();
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
