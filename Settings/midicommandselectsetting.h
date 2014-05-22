#ifndef MIDICOMMANDSELECTSETTING_H
#define MIDICOMMANDSELECTSETTING_H

#include <QStringList>
#include "Settings/setting.h"
#include "Domain/domain.h"

class NordStage2Node;
class MidiCommandSelectSetting : public Setting
{
    Q_OBJECT
public:
    MidiCommandSelectSetting(NordStage2Node *parent, QString name, QString tooltip);
    ~MidiCommandSelectSetting();


    double min() const;
    double max() const;
    double value() const;
    int index() const;
    QStringList items() const;

    QStringList categories() const;
    QStringList properties() const;
    void setCategoryIndex(int i);
    void setPropertyIndex(int i);
    Domain::Type domainType() const;
    Domain* domain() const;


    int currentCategory() const { return _currentCategory; }
    int currentProperty() const { return _currentProperty; }

public slots:
    void setDouble(double d);
    void setInt(int i);
    void setIndex(int i);
    void setCategory(int i);
    void setProperty(int i);
private:
    int _currentCategory = 0;
    int _currentProperty = 0;
    QString key() const {
        return QString("%1.%2")
                .arg(categories()[_currentCategory])
                .arg(properties()[_currentProperty]); }
    quint8 midicode() const;
    int channel = 0;


signals:
    void sendMidi();


};

#endif // MIDICOMMANDSELECTSETTING_H
