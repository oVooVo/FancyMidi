#ifndef MIDICOMMANDSELECTSETTING_H
#define MIDICOMMANDSELECTSETTING_H

#include <QStringList>
#include "Settings/setting.h"
#include "Domain/domain.h"
#include <QDebug>
#include "nordstage2.h"
#include <QDataStream>

class MidiCommandSelectSetting : public Setting
{
    Q_OBJECT

public:
    MidiCommandSelectSetting(Node *parent, QString name, QString tooltip, bool showInNode = true);
    MidiCommandSelectSetting(QDataStream& stream);
    void writeToStream(QDataStream &stream) const;
    ~MidiCommandSelectSetting();


    double min() const;
    double max() const;
    double value() const;
    int index() const;
    QStringList items() const;

    Domain::Type domainType() const;
    Domain* domain() const { return _domain; }


    int currentCategory() const { return _currentCategory; }
    int currentProperty() const { return _currentProperty; }

    void connectPort(DataInputPort *category, DataInputPort *property, DataInputPort* value);

    bool categoryEnabled() const { return _categoryEnabled; }
    bool propertyEnabled() const { return _propertyEnabled; }
    bool valueEnabled() const { return _valueEnabled; }


public slots:
    void setValue(QVariant v);
    void setCategoryIndex(int i);
    void setPropertyIndex(int i);

    void setCategoryEnabled(bool enabled);
    void setPropertyEnabled(bool enabled);
    void setValueEnabled(bool enabled);


private:
    int _currentCategory = 0;
    int _currentProperty = 0;
    QString key() const {
        return QString("%1.%2")
                .arg(NordStage2::categories()[_currentCategory])
                .arg(NordStage2::properties(_currentCategory)[_currentProperty]); }
    MidiKey midiKey() const;
    Domain* _domain = 0;
    void updateDomain();
    QVariant _value;

    bool _categoryEnabled = true;
    bool _propertyEnabled = true;
    bool _valueEnabled = true;

signals:
    void sendMidi();
    void categoryEnabledChanged(bool);
    void propertyEnabledChanged(bool);
    void valueEnabledChanged(bool);

    REGISTER_DECL_SETTINGTYPE(MidiCommandSelectSetting);
};

#endif // MIDICOMMANDSELECTSETTING_H
