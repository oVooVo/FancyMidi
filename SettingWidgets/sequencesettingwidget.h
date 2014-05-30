#ifndef SEQUENCESETTINGWIDGET_H
#define SEQUENCESETTINGWIDGET_H

#include "settingwidget.h"
#include <QLineEdit>



class SequenceSettingWidget : public SettingWidget
{
    Q_OBJECT
public:
    explicit SequenceSettingWidget(Setting *set, QWidget *parent = 0);

private:
    QLineEdit* _sequenceEdit;
    QLabel* _lengthLabel;
    REGISTER_DECL_SETTINGWIDGETTYPE(SequenceSettingWidget);

public slots:
    void reset();

};

#endif // SEQUENCESETTINGWIDGET_H
