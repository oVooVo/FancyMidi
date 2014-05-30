#pragma once

#include <QString>
#include <QDataStream>
#include <QWidget>
#include <QObject>
#include "Model/Nodes/node.h"
#include "Model/port.h"
#include <QByteArray>
#include "numbered.h"

class SettingWidget;


class Setting;
template<typename T> Setting *createSetting(QDataStream& data) { return new T(data); }

/**
 * @brief The Setting class is the abstract model of handling preferences
 */
class Setting : public QObject, public Numbered
{
Q_OBJECT

protected:
    Setting(QDataStream &stream);
public:
    /**
     * @brief Setting Creates a settings object with a given name and a description
     * @param parent The parent for the QObject
     * @param name The given name
     * @param infoText The given description
     */
    Setting(Node *parent, QString name, QString tooltip, bool showInNode = true);

    ~Setting();

    /**
     * @brief getName Returns the name of this setting
     * @return Returns The name of this setting
     */
    const QString name() const;
    /**
     * @brief getInfoText Returns the description of this setting
     * @return Returns The description of this setting
     */
    const QString tooltip() const;

    /**
     * @brief emitChanged emits a changed signal and stops the project.
     */
    void emitChanged();

    bool showInNode() const { return _showInNode; }

    bool isEnabled() const { return _isEnabled; }

    virtual void connectPort(DataInputPort*) {}

public slots:
    void setEnabled(bool enabled);

signals:

    /**
     * @brief changed is emitted when any value of this setting changes.
     */
    void changed();
    void enabledChanged(bool enabled);

protected:
    const Node* constNode() const { return (const Node*) parent(); }

    virtual void writeToStream(QDataStream& stream) const;
    static QMap<QString, Setting* (*)(QDataStream&)> *_creatorMap;
    static Setting *createInstance(QString className, QDataStream&stream);

private:
    Node* node();
    QString _name;
    QString _tooltip;
    bool _showInNode;
    bool _isEnabled = true;

    friend QDataStream &operator<<(QDataStream &out, const Setting *setting);
    friend QDataStream &operator>>(QDataStream &in, Setting *&setting);
};

template<typename T>
struct SettingRegister : Setting
{
    SettingRegister(QString className) : Setting(0, "", "")
    {
        if (!_creatorMap)
            _creatorMap = new QMap<QString, Setting* (*)(QDataStream&)>();
        _creatorMap->insert(className, &createSetting<T>);
    }
};

#define REGISTER_DECL_SETTINGTYPE(CLASSNAME) \
private:    \
    static SettingRegister<CLASSNAME> reg

#define REGISTER_DEFN_SETTINGTYPE(CLASSNAME) \
    SettingRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

QDataStream &operator<<(QDataStream &out, const Setting *setting);
QDataStream &operator>>(QDataStream &in, Setting *&setting);

