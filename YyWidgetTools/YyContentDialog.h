#ifndef YyCONTENTDIALOG_H
#define YyCONTENTDIALOG_H
#include <QAbstractNativeEventFilter>
#include <QDialog>

#include "YyAppBar.h"
#include "YyProperty.h"
class YyContentDialogPrivate;
class Yy_EXPORT YyContentDialog : public QDialog
{
    Q_OBJECT
    Q_Q_CREATE(YyContentDialog)
    Q_TAKEOVER_NATIVEEVENT_H
public:
    explicit YyContentDialog(QWidget* parent);
    ~YyContentDialog() override;
    Q_SLOT virtual void onLeftButtonClicked();
    Q_SLOT virtual void onMiddleButtonClicked();
    Q_SLOT virtual void onRightButtonClicked();
    void setCentralWidget(QWidget* centralWidget);

    void setLeftButtonText(QString text);
    void setMiddleButtonText(QString text);
    void setRightButtonText(QString text);

    void close();
Q_SIGNALS:
    Q_SIGNAL void leftButtonClicked();
    Q_SIGNAL void middleButtonClicked();
    Q_SIGNAL void rightButtonClicked();

protected:
    virtual void showEvent(QShowEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
};

#endif // YyCONTENTDIALOG_H
