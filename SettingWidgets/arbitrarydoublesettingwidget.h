/*
 * #ifndef ARBITRARYDOUBLESETTINGWIDGET_H
#define ARBITRARYDOUBLESETTINGWIDGET_H

#include <QWidget>
#include "SettingWidgets/settingwidget.h"

namespace Ui {
class ArbitraryDoubleSettingWidget;
}

class ArbitraryDoubleSettingWidget : public SettingWidget
{
    Q_OBJECT

public:
    explicit ArbitraryDoubleSettingWidget(Setting* set, QWidget *parent = 0);
    ~ArbitraryDoubleSettingWidget();

public slots:
    void reset();
    REGISTER_DECL_SETTINGWIDGETTYPE(ArbitraryDoubleSettingWidget);

private:
    Ui::ArbitraryDoubleSettingWidget *ui;
    QString _lastValidText;
};

#endif // ARBITRARYDOUBLESETTINGWIDGET_H
*/
