#include "YyApplication.h"

#include "YyTheme.h"
#include "YyWinShadowHelper.h"
#include "private/YyApplicationPrivate.h"
#include <QApplication>
#include <QCursor>
#include <QFontDatabase>
#include <QWidget>
#include <utility>
Q_SINGLETON_CREATE_CPP(YyApplication)
YyApplication::YyApplication(QObject* parent)
    : QObject{parent}, d_ptr(new YyApplicationPrivate())
{
    Q_D(YyApplication);
    d->q_ptr = this;
    d->_pYyMicaImagePath = ":/include/Image/MicaBase.png";
    d->_pWindowDisplayMode = YyApplicationType::Normal;
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, d, &YyApplicationPrivate::onThemeModeChanged);
}

YyApplication::~YyApplication()
{
}

void YyApplication::setWindowDisplayMode(YyApplicationType::WindowDisplayMode windowDisplayType)
{
    Q_D(YyApplication);
    auto lastDisplayMode = d->_pWindowDisplayMode;
    if (lastDisplayMode == windowDisplayType)
    {
        return;
    }
    if (lastDisplayMode == YyApplicationType::YyMica)
    {
        d->_resetAllMicaWidget();
    }
    switch (windowDisplayType)
    {
    case YyApplicationType::Normal:
    {
        break;
    }
    case YyApplicationType::YyMica:
    {
        d->_pWindowDisplayMode = windowDisplayType;
        d->_initMicaBaseImage(QImage(d->_pYyMicaImagePath));
        break;
    }
    default:
    {
        break;
    }
    }
#ifdef Q_OS_WIN
    for (auto widget: d->_micaWidgetList)
    {
        YyWinShadowHelper::getInstance()->setWindowDisplayMode(widget, windowDisplayType, lastDisplayMode);
        YyWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), d->_themeMode == YyThemeType::Light);
    }
#endif
    if (windowDisplayType != YyApplicationType::YyMica)
    {
        d->_pWindowDisplayMode = windowDisplayType;
        Q_EMIT pWindowDisplayModeChanged();
    }
}

YyApplicationType::WindowDisplayMode YyApplication::getWindowDisplayMode() const
{
    Q_D(const YyApplication);
    return d->_pWindowDisplayMode;
}

void YyApplication::setYyMicaImagePath(QString micaImagePath)
{
    Q_D(YyApplication);
    d->_pYyMicaImagePath = std::move(micaImagePath);
    d->_initMicaBaseImage(QImage(d->_pYyMicaImagePath));
    Q_EMIT pYyMicaImagePathChanged();
}

QString YyApplication::getYyMicaImagePath() const
{
    Q_D(const YyApplication);
    return d->_pYyMicaImagePath;
}

void YyApplication::init()
{
    Q_INIT_RESOURCE(YyWidgetTools);
    QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    int fontId = QFontDatabase::addApplicationFont(":/include/Font/YyAwesome.ttf");

    if (fontId == -1) {
        qDebug() << "字体加载失败！路径错误或文件损坏";
    } else {
        qDebug() << "字体加载成功！";
    }

    QString realFontName = QFontDatabase::applicationFontFamilies(fontId).first();
    qDebug() << "字体名称 :" << realFontName;

    //默认字体
    QFont font = qApp->font();
    font.setPixelSize(13);
    font.setFamily("Microsoft YaHei");
    font.setHintingPreference(QFont::PreferNoHinting);
    qApp->setFont(font);
#ifdef Q_OS_WIN
    eWinHelper->initWinAPI();
#endif
}

void YyApplication::syncWindowDisplayMode(QWidget* widget, bool isSync)
{
    Q_D(YyApplication);
    if (!widget)
    {
        return;
    }
    if (isSync)
    {
        d->_micaWidgetList.append(widget);
        widget->installEventFilter(d);
    }
    else
    {
        d->_micaWidgetList.removeOne(widget);
        widget->removeEventFilter(d);
    }
    switch (d->_pWindowDisplayMode)
    {
    case YyApplicationType::Normal:
    case YyApplicationType::YyMica:
    {
        if (isSync)
        {
            if (d->_pWindowDisplayMode == YyApplicationType::WindowDisplayMode::YyMica)
            {
                d->_updateMica(widget, false);
            }
        }
        break;
    }
    default:
    {
#ifdef Q_OS_WIN
        if (isSync)
        {
            YyWinShadowHelper::getInstance()->setWindowDisplayMode(widget, d->_pWindowDisplayMode, YyApplicationType::Normal);
            YyWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), d->_themeMode == YyThemeType::Light);
        }
        else
        {
            YyWinShadowHelper::getInstance()->setWindowDisplayMode(widget, YyApplicationType::Normal, d->_pWindowDisplayMode);
            YyWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), true);
        }
#endif
        break;
    }
    }
}

bool YyApplication::containsCursorToItem(QWidget* item)
{
    if (!item || !item->isVisible())
    {
        return false;
    }
    auto point = item->window()->mapFromGlobal(QCursor::pos());
    QRectF rect = QRectF(item->mapTo(item->window(), QPoint(0, 0)), item->size());
    if (rect.contains(point))
    {
        return true;
    }
    return false;
}
