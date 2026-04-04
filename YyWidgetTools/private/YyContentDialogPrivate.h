#ifndef YyCONTENTDIALOGPRIVATE_H
#define YyCONTENTDIALOGPRIVATE_H

#include <QObject>

#include "YyDef.h"
class QVBoxLayout;
class YyPushButton;
class YyContentDialog;
class YyMaskWidget;
class YyAppBar;
class YyContentDialogPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyContentDialog)
public:
    explicit YyContentDialogPrivate(QObject* parent = nullptr);
    ~YyContentDialogPrivate() override;

private:
    qint64 _currentWinID{0};
    YyAppBar* _appBar{nullptr};
    YyThemeType::ThemeMode _themeMode;
    YyMaskWidget* _maskWidget{nullptr};
    QWidget* _centralWidget{nullptr};
    QWidget* _buttonWidget{nullptr};
    QVBoxLayout* _mainLayout{nullptr};
    QString _leftButtonText{"cancel"};
    QString _middleButtonText{"minimum"};
    QString _rightButtonText{"exit"};
    YyPushButton* _leftButton{nullptr};
    YyPushButton* _middleButton{nullptr};
    YyPushButton* _rightButton{nullptr};
    void _doCloseAnimation(bool isAccept);
};

#endif // YyCONTENTDIALOGPRIVATE_H
