#pragma once

#include <QString>
#include <QDataStream>
#include <QWidget>
#include <QObject>
#include "Model/node.h"

class SettingWidget;

/**
 * @brief The Setting class is the abstract model of handling preferences
 */
class Setting:
	public QObject
{
Q_OBJECT

public:
    /**
     * @brief Setting Creates a settings object with a given name and a description
     * @param parent The parent for the QObject
     * @param name The given name
     * @param infoText The given description
     */
    Setting(Node *parent, QString name, QString tooltip);

    ~Setting();

    /**
     * @brief getName Returns the name of this setting
     * @return Returns The name of this setting
     */
    const QString getName() const;
    /**
     * @brief getInfoText Returns the description of this setting
     * @return Returns The description of this setting
     */
    const QString tooltip() const;

    /**
     * @brief setValid sets or removes the valid flag.
     * @param valid sets or removes the valid flag.
     */
    void setValid(bool valid);

    /**
     * @brief isValid returns whether this setting is adjusted validly.
     * @return whether this setting is adjusted validly.
     */
    bool isValid() const;

    /**
     * @brief emitChanged emits a changed signal and stops the project.
     */
    void emitChanged();

signals:
    /**
     * @brief validChange is emitted when the valid status of this setting changes.
     */
    void validChange();

    /**
     * @brief changed is emitted when any value of this setting changes.
     */
    void changed();

protected:
    const Node* constNode() const { return (const Node*) parent(); }

private:
    Node* node();
    Q_DISABLE_COPY(Setting)
    QString _name;
    QString _tooltip;
    bool _isValid;
};

QDataStream &operator<<(QDataStream &out, const Setting *setting);
QDataStream &operator>>(QDataStream &in, Setting *&setting);

