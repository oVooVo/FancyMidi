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
    _categoryIndex = qBound(0, category, NordStage2::categories().length() - 1);
    _propertyIndex = 0;

    emitChanged();
    emit categoryChanged(category);
}

void MidiFilterSetting::setPropertyIndex(int property)
{
    _propertyIndex = qBound(0, property, NordStage2::properties(_categoryIndex).length() - 1);
    emitChanged();
    emit propertyChanged(property);
}

void MidiFilterSetting::setChannel(int channel)
{
    _channel = qBound(0, channel, Keyboard::NUM_MIDI_CHANNELS - 1);
    emitChanged();
    emit channelChanged(channel);
}

void MidiFilterSetting::setTypeIndex(int type)
{
    _typeIndex = qBound(0, type, 6);
    emitChanged();
    emit typeChanged(type);
}

void MidiFilterSetting::setFilterCategory(bool filter)
{
    _filterCategory = filter;
    emitChanged();
}

void MidiFilterSetting::setFilterProperty(bool filter)
{
    _filterProperty = filter;
    emitChanged();
}

void MidiFilterSetting::setFilterChannel(bool filter)
{
    _filterChannel = filter;
    emitChanged();
}

void MidiFilterSetting::setFilterType(bool filter)
{
    if (_filterType == filter || !isEnabled())
        return;

    _filterType = filter;
    emitChanged();
}

MidiKey::MidiType MidiFilterSetting::type() const
{
    switch (_typeIndex) {
    case 0: return MidiKey::NoteOn;
    case 1: return MidiKey::NoteOff;
    case 2: return MidiKey::ControlChange;
    case 3: return MidiKey::ProgramChange;
    case 4: return MidiKey::PitchBend;
    case 5: return MidiKey::Aftertouch;
    default:
        return MidiKey::Unknown;
    }
}
