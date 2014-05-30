#ifndef INFOSETTING_H
#define INFOSETTING_H

#include "setting.h"


class InfoSetting : public Setting
{
    Q_OBJECT
public:
    InfoSetting(QDataStream &stream);
    InfoSetting(Node* parent, QString name, QString tooltip, QString text, bool showInNode = true);

    void setString(const QString& string);
    QString string() const { return _string; }

private:
    QString _string;
    REGISTER_DECL_SETTINGTYPE(InfoSetting);

};

#endif // INFOSETTING_H
