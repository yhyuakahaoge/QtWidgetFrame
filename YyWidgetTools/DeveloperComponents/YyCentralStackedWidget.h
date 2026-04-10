#ifndef YyCENTRALSTACKEDWIDGET_H
#define YyCENTRALSTACKEDWIDGET_H

#include <QStackedWidget>

#include "YyDef.h"
#include <QVBoxLayout>
class QGraphicsBlurEffect;
class YyCentralStackedWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY_CREATE(int, PopupAnimationYOffset)
    Q_PROPERTY_CREATE(qreal, ScaleAnimationRatio)
    Q_PROPERTY_CREATE(qreal, ScaleAnimationPixOpacity)
    Q_PROPERTY_CREATE(qreal, FlipAnimationRatio)
    Q_PROPERTY_CREATE(int, BlurAnimationRadius)
public:
    explicit YyCentralStackedWidget(QWidget* parent = nullptr);
    ~YyCentralStackedWidget() override;

    QStackedWidget* getContainerStackedWidget() const;

    void setCustomWidget(QWidget* widget);
    QWidget* getCustomWidget() const;

    Q_SLOT void onThemeModeChanged(YyThemeType::ThemeMode themeMode);

    void setIsTransparent(bool isTransparent);
    bool getIsTransparent() const;

    void setIsHasRadius(bool isHasRadius);

    void doWindowStackSwitch(YyWindowType::StackSwitchMode stackSwitchMode, int nodeIndex, bool isRouteBack);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    YyWindowType::StackSwitchMode _stackSwitchMode{YyWindowType::StackSwitchMode::Popup};
    YyThemeType::ThemeMode _themeMode;
    QPixmap _targetStackPix;
    QPixmap _currentStackPix;
    QGraphicsBlurEffect* _blurEffect{nullptr};
    bool _isTransparent{false};
    QVBoxLayout* _mainLayout{nullptr};
    QWidget* _customWidget{nullptr};
    QStackedWidget* _containerStackedWidget{nullptr};
    bool _isHasRadius{true};
    bool _isDrawNewPix{false};
    void _getTargetStackPix();
    void _getCurrentStackPix();
};

#endif // YyCENTRALSTACKEDWIDGET_H
