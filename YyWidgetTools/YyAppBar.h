#ifndef YYAPPBAR_H
#define YYAPPBAR_H

#include <QWidget>
#include "YyDef.h"

#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define Q_TAKEOVER_NATIVEEVENT_H virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#else
#define Q_TAKEOVER_NATIVEEVENT_H virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#endif
#else
#define Q_TAKEOVER_NATIVEEVENT_H
#endif

#ifdef Q_OS_WIN
#define YYAPPBAR_HANDLE(YyAppBar)                                           \
if (YyAppBar)                                                            \
    {                                                                         \
            int ret = YyAppBar->takeOverNativeEvent(eventType, message, result); \
            if (ret == -1)                                                        \
        {                                                                     \
                return QWidget::nativeEvent(eventType, message, result);          \
        }                                                                     \
            return (bool)ret;                                                     \
    }                                                                         \
    return QWidget::nativeEvent(eventType, message, result);
#endif

#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, YyAppBar)                                     \
bool CLASS::nativeEvent(const QByteArray& eventType, void* message, qintptr* result) \
{                                                                                    \
        YYAPPBAR_HANDLE(YyAppBar)                                                      \
}
#else
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, YyAppBar)                                  \
bool CLASS::nativeEvent(const QByteArray& eventType, void* message, long* result) \
{                                                                                 \
        YYAPPBAR_HANDLE(YyAppBar)                                                   \
}
#endif
#else
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, YyAppBar)
#endif

class QMenu;
class YyAppBarPrivate;
class Yy_EXPORT YyAppBar : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(YyAppBar)
    Q_PROPERTY_CREATE_Q_H(bool, IsStayTop)
    Q_PROPERTY_CREATE_Q_H(bool, IsFixedSize)
    Q_PROPERTY_CREATE_Q_H(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_Q_H(bool, IsOnlyAllowMinAndClose)
    Q_PROPERTY_CREATE_Q_H(int, AppBarHeight)
public:
    explicit YyAppBar(QWidget* parent = nullptr);
    virtual ~YyAppBar() override;

#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    int takeOverNativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
    int takeOverNativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
#endif

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event) override;
#ifdef Q_OS_WIN
    virtual void paintEvent(QPaintEvent* event) override;
#endif
};

#endif // YYAPPBAR_H
