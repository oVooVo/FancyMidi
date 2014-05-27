#include "midifiltersetting.h"
#include <QThread>
#include <QApplication>
#include <QDebug>
#include "nordstage2.h"

REGISTER_DEFN_SETTINGTYPE(MidiFilterSetting);

MidiFilterSetting::MidiFilterSetting(Node *parent, QString name, QString tooltip, bool showInNode):
    Setting(parent, name, tooltip, showInNode)
{
}

MidiFilterSetting::~MidiFilterSetting()
{

}

MidiFilterSetting::MidiFilterSetting(QDataStream &stream)
    : Setting(stream)
{
    stream >> _channel >> _propertyIndex >> _typeIndex >> _categoryIndex
           >> _filterChannel >> _filterProperty >> _filterType >> _filterCategory;
}

void MidiFilterSetting::writeToStream(QDataStream &stream) const
{
    Setting::writeToStream(stream);
    stream << _channel << _propertyIndex << _typeIndex << _categoryIndex
           << _filterChannel << _filterProperty << _filterType << _filterCategory;
}

void MidiFilterSetting::setCategoryIndex(int category)
{
    if (category == _categoryIndex)
        return;

    _categoryIndex = qBound(0, category, NordStage2::categories().length() - 1);
    _propertyIndex = 0;

    emitChanged();
}

void MidiFilterSetting::setPropertyIndex(int property)
{
    if (property == _propertyIndex)
        return;

    _propertyIndex = qBound(0, property, NordStage2::properties(_categoryIndex).length() - 1);
    emitChanged();
}

void MidiFilterSetting::setChannel(int channel)
{
    if (channel == _channel)
        return;

    _channel = qBound(0, channel, Keyboard::NUM_MIDI_CHANNELS - 1);
    emit changed();
}

void MidiFilterSetting::setTypeIndex(int type)
{
    if (type == _typeIndex)
        return;

    _typeIndex = qBound(0, type, 6);
    emit changed();
}

void MidiFilterSetting::setFilterCategory(bool filter)
{
    if (_filterCategory == filter)
        return;

    _filterCategory = filter;
    emit changed();
}

void MidiFilterSetting::setFilterProperty(bool filter)
{
    if (_filterProperty == filter)
        return;

    _filterProperty = filter;
    emit changed();
}

void MidiFilterSetting::setFilterChannel(bool filter)
{
    if (_filterChannel == filter)
        return;

    _filterChannel = filter;
    emit changed();
}

void MidiFilterSetting::setFilterType(bool filter)
{
    if (_filterType == filter)
        return;

    _filterType = filter;
    emit changed();
}

MidiKey::MidiType MidiFilterSetting::type() const
{
    switch (_typeIndex) {
    case 0: return MidiKey::NoteOn;
    case 1: return MidiKey::NoteOff;
    case 2: return MidiKey::ControlChange;
    case 3: return MidiKey::ProgramChange;
    case 4: return MidiKey::PitchBend;
    default:
        return MidiKey::Unknown;
    }
}
