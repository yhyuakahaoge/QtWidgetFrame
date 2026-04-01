#ifndef YyWINDOWPRIVATE_H
#define YyWINDOWPRIVATE_H

#include "YyDef.h"

class QLabel;
class QScreen;
class QHBoxLayout;
class QVBoxLayout;
class YyText;
class YyAppBar;
class YyIconButton;
class YyToolButton;
class QMenu;
class YyAppBarPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YyAppBar)
    Q_PROPERTY_CREATE_D(bool, IsStayTop)
    Q_PROPERTY_CREATE_D(bool, IsFixedSize)
    Q_PROPERTY_CREATE_D(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_D(bool, IsOnlyAllowMinAndClose)
    Q_PROPERTY_CREATE_D(int, AppBarHeight)
public:
    explicit YyAppBarPrivate(QObject* parent = nullptr);
    virtual ~YyAppBarPrivate() override;
    Q_SLOT void onMinButtonClicked();
    Q_SLOT void onMaxButtonClicked();
    Q_SLOT void onCloseButtonClicked();
    Q_SLOT void onStayTopButtonClicked();
private:
    YyThemeType::ThemeMode _themeMode;
    QHBoxLayout* _mainLayout{nullptr};
    QVBoxLayout* _iconLabelLayout{nullptr};
    QVBoxLayout* _titlYybelLayout{nullptr};
    YyAppBarType::ButtonFlags _buttonFlags;
    YyToolButton* _routeBackButton{nullptr};
    YyToolButton* _routeForwardButton{nullptr};
    YyToolButton* _navigationButton{nullptr};
    YyToolButton* _themeChangeButton{nullptr};
    YyToolButton* _stayTopButton{nullptr};
    YyToolButton* _minButton{nullptr};
    YyToolButton* _maxButton{nullptr};
    YyIconButton* _closeButton{nullptr};
    QList<QWidget*> _customAreaWidgetList{nullptr, nullptr, nullptr};
    QList<QObject*> _customAreaHitTestObjectList{nullptr, nullptr, nullptr};
    QStringList _customAreaHitTestFunctionNameList{"", "", ""};
    QList<QWidget*> _clientWidgetList;
    QScreen* _lastScreen{nullptr};
    YyText* _titlYybel{nullptr};
    QLabel* _iconLabel{nullptr};
    qint64 _currentWinID{0};
    int _lastMinTrackWidth{0};
    quint64 _clickTimer{0};
    int _edges{0};
    int _margins{8};
    bool _isHoverMaxButton{false};
    int _win7Margins{0};
    QMenu *_pCustomMenu;
    void _changeMaxButtonAwesome(bool isMaximized);
    void _showAppBarMenu(QPoint point);
    void _updateCursor(int edges);
    bool _containsCursorToItem(QWidget* item);
    void _onThemeModeChange(YyThemeType::ThemeMode themeMode);
    int _calculateMinimumWidth();
    QVBoxLayout* _createVLayout(QWidget* widget);
};

#endif // YyWINDOWPRIVATE_H
