#pragma once

#include <QWidget>
#include "Settings/setting.h"
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QMap>


#define CHECK_SETTING(SETTING_CLASS) \
    Q_ASSERT(QString(set->metaObject()->className()) == QString(SETTING_CLASS::staticMetaObject.className()))

#define SETTINGWIDGET_CREATOR_MAP_TYPE QMap<QString, SettingWidget* (*)(Setting* setting, QWidget* parent)>
template<typename T> SettingWidget *createSettingWidget(Setting* setting, QWidget* parent) {
    return new T(setting, parent);
}


/**
 * @brief The SettingWidget class is a widget representing the Setting class
 * @see Setting
 */
class SettingWidget : public QWidget
{
    Q_OBJECT
protected:
    /**
     * @brief SettingWidget Creates a SettingWidget on the given parent QWidget
     * @param parent The given parent QWidget
     */
    explicit SettingWidget(Setting* setting, QWidget *parent = 0);

public:
    /**
     * @brief createNewSettingWidget creates a new SettingWidget with a given Setting and parent.
     * @param setting the setting this SettingWidget is associated with.
     * @param parent the parent QWidget of this SettingWidget.
     * @return the new SettingWidget.
     */
    static SettingWidget* createNewSettingWidget(Setting *setting, QWidget *parent = 0);

public slots:
    /**
     * @brief reset resets the widget after it's setting object became changed.
     */
    virtual void reset() = 0;

protected:
    /**
     * @brief paintEvent is called when the Widget has to be redrawn.
     * @param event the event.
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief _initMode whether this widget changes due to initial draw.
     */
    bool _initMode;

    /**
     * @brief _setting the setting associated with this SettingWidget.
     */
    Setting* _setting;

public:
    template<typename T> T* setting() const { return (T*) _setting; }

private:
    static SETTINGWIDGET_CREATOR_MAP_TYPE *_creatorMap;

    //allows to keep _creatorMap private since _creatorMap is an implementation detail.
    template<typename T> friend class SettingWidgetRegister;

};


template<typename T>
struct SettingWidgetRegister
{
    SettingWidgetRegister(QString className)
    {
        if (!SettingWidget::_creatorMap) //create new _creatorMap if there wasnt one.
            SettingWidget::_creatorMap = new SETTINGWIDGET_CREATOR_MAP_TYPE();
        // insert constructor of registered type with classname-key.
        SettingWidget::_creatorMap->insert(className, &createSettingWidget<T>);
    }
};


#define REGISTER_DECL_SETTINGWIDGETTYPE(CLASSNAME) \
private: \
static SettingWidgetRegister<CLASSNAME> reg

#define REGISTER_DEFN_SETTINGWIDGETTYPE(CLASSNAME) \
SettingWidgetRegister<CLASSNAME> CLASSNAME::reg(#CLASSNAME)

