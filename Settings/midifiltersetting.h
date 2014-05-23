#ifndef MIDIFILTERSETTING_H
#define MIDIFILTERSETTING_H

#include <QStringList>
#include "Settings/setting.h"
#include "Domain/domain.h"
#include <QDebug>



class MidiFilterSetting : public Setting
{
    Q_OBJECT
public:
    MidiFilterSetting(Node *parent, QString name, QString tooltip);
    ~MidiFilterSetting();

    int categoryIndex() const { return _categoryIndex; }
    int propertyIndex() const { return _propertyIndex; }
    int channel() const { return _channel; }
    int typeIndex() const { return _typeIndex; }
    bool filterCategory() const { return _filterCategory; }
    bool filterProperty() const { return _filterProperty; }
    bool filterType() const { return _filterType; }
    bool filterChannel() const { return _filterChannel; }
    MidiKey::MidiType type() const;

public slots:
    void setCategoryIndex(int category);
    void setPropertyIndex(int property);
    void setChannel(int channel);
    void setTypeIndex(int type);
    void setFilterCategory(bool filter);
    void setFilterProperty(bool filter);
    void setFilterChannel(bool filter);
    void setFilterType(bool filter);


private:
    int _channel = 0;
    int _propertyIndex = 0;
    int _typeIndex = 0;
    int _categoryIndex = 0;
    bool _filterChannel = false;
    bool _filterProperty = false;
    bool _filterType = false;
    bool _filterCategory = false;


};

#endif // MIDIFILTERSETTING_H
