#include "YyCustomWidget.h"

#include <QPainter>
#include <QVBoxLayout>

#include "YyApplication.h"
#include "YyTheme.h"
Q_TAKEOVER_NATIVEEVENT_CPP(YyCustomWidget, _appBar);
YyCustomWidget::YyCustomWidget(QWidget* parent)
    : QDialog{parent}
{
    resize(500, 500); // 默认宽高
    setObjectName("YyCustomWidget");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowFullscreenButtonHint);
#if (QT_VERSION < QT_VERSION_CHECK(6, 5, 3) || QT_VERSION > QT_VERSION_CHECK(6, 6, 1))
    setStyleSheet("#YyCustomWidget{background-color:transparent;}");
#endif
    // 自定义AppBar
    _appBar = new YyAppBar(this);
    _appBar->setWindowButtonFlags(YyAppBarType::MinimizeButtonHint | YyAppBarType::MaximizeButtonHint | YyAppBarType::CloseButtonHint);
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setContentsMargins(0, 0, 0, 0);

    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
        update();
    });

    _windowDisplayMode = eApp->getWindowDisplayMode();
    connect(eApp, &YyApplication::pWindowDisplayModeChanged, this, [=]() {
        _windowDisplayMode = eApp->getWindowDisplayMode();
        update();
    });
    eApp->syncWindowDisplayMode(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

YyCustomWidget::~YyCustomWidget()
{
    eApp->syncWindowDisplayMode(this, false);
}

void YyCustomWidget::setCentralWidget(QWidget* widget)
{
    if (!widget)
    {
        return;
    }
    _centralWidget = widget;
    _mainLayout->addWidget(widget);
    widget->setVisible(true);
}

void YyCustomWidget::paintEvent(QPaintEvent* event)
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
    if (_windowDisplayMode != YyApplicationType::WindowDisplayMode::YyMica)
#else
    if (_windowDisplayMode == YyApplicationType::WindowDisplayMode::Normal)
#endif
    {
        QPainter painter(this);
        painter.save();
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(YyThemeColor(_themeMode, WindowBase));
        painter.drawRect(rect());
        painter.restore();
    }
}
