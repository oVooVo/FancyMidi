#include "sequencesettingwidget.h"
#include "../Settings/sequencesetting.h"

REGISTER_DEFN_SETTINGWIDGETTYPE(SequenceSettingWidget);

SequenceSettingWidget::SequenceSettingWidget(Setting* set, QWidget *parent) :
    SettingWidget(set, parent)
{
    Q_ASSERT(QString(set->metaObject()->className()) == QString(SequenceSetting::staticMetaObject.className()));
    QVBoxLayout* layout = new QVBoxLayout(this);
    _sequenceEdit = new QLineEdit(this);
    _lengthLabel = new QLabel(this);
    layout->addWidget(_sequenceEdit);
    layout->addWidget(_lengthLabel);
    setLayout(layout);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    _sequenceEdit->setPlaceholderText("Type Sequence ...");
    connect(_sequenceEdit, &QLineEdit::textChanged, [this](const QString& text){
        int  cursorPosition = _sequenceEdit->cursorPosition();
        QString replaced = text;
        replaced.replace(QRegExp("\\+|#|(IS)|(is)"), SequenceSetting::SHARP);
        replaced.replace(QRegExp("-|p|s"), SequenceSetting::FLAT);
        replaced.replace(QRegExp("´|`"), SequenceSetting::OCTAVE_UP);
        replaced.replace(QRegExp("\\."), SequenceSetting::OCTAVE_DOWN);
        if (setting<SequenceSetting>()->setSequence(replaced)) {
            _sequenceEdit->setStyleSheet("QLineEdit { background-color: white }");
        } else {
            _sequenceEdit->setStyleSheet("QLineEdit { background-color: #FF8888 }");
        }
        _sequenceEdit->setText(replaced.toUpper());
        _sequenceEdit->setCursorPosition(cursorPosition);
        _lengthLabel->setText(QString("Length: %1").arg(
                                  setting<SequenceSetting>()->length()));
    });
    reset();
}

void SequenceSettingWidget::reset()
{
    _sequenceEdit->setText(setting<SequenceSetting>()->sequence());
    _lengthLabel->setText(QString("Length: %1").arg(
                              setting<SequenceSetting>()->length()));
}
