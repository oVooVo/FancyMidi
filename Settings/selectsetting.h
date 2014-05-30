#pragma once

#include <QString>
#include <QList>
#include "setting.h"
#include "scalarsetting.h"

/**
 * @brief The SelectSetting class is the model of handling selecting based preferences
 * @see Setting
 */
class SelectSetting : public ScalarSetting<int>
{
    Q_OBJECT

public:
    /**
     * @brief SelectSetting Creates a SelectSetting object, used for choosing between a variety of things (e.g. algorithms)
     * @param parent The parent for QObject
     * @param name Name of the selection (@see setting)
     * @param infoText Text display in the tooltip (@see setting)
     * @param defaultEntry Set the value chosen by default, it has to be a number existing in the given map
     * @param values Contains all things to be chosen from (String and a int)
     */
    SelectSetting(Node *parent, QString name, QString infoText, int currentIndex, QList<QString> values, int defaultValue,
                  bool showInNode = true);
    SelectSetting(QDataStream &stream);
    virtual void writeToStream(QDataStream& stream) const;


    ~SelectSetting();

    /**
     * @brief getList Get the list containing all entries
     * @return Returns the list containing all entries
     */
    const QList<QString> values() const;

public slots:
    /**
     * @brief setCurrentIndex Sets the given index as current setting
     * @warning If the given index is not in the list nothing is done
     * @param index The given entry
     */
    void setValue(int index) { ScalarSetting::setValue(index); }

private:
    QList<QString> _values;

    REGISTER_DECL_SETTINGTYPE(SelectSetting);
};
