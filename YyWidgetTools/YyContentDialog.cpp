#include "YyContentDialog.h"

#include "YyPushButton.h"

#include "YyMaskWidget.h"
#include "YyText.h"
#include "YyTheme.h"
#include "YyWinShadowHelper.h"
#include "private/YyContentDialogPrivate.h"
#include <QApplication>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
Q_TAKEOVER_NATIVEEVENT_CPP(YyContentDialog, d_func()->_appBar);
YyContentDialog::YyContentDialog(QWidget* parent)
    : QDialog{parent}, d_ptr(new YyContentDialogPrivate())
{
    Q_D(YyContentDialog);
    d->q_ptr = this;

    d->_maskWidget = new YyMaskWidget(parent);
    d->_maskWidget->move(0, 0);
    d->_maskWidget->setFixedSize(parent->size());
    d->_maskWidget->setVisible(false);

    resize(400, height());
    // 聚焦此dialog窗口 其他窗口不可操作
    setWindowModality(Qt::ApplicationModal);

    d->_appBar = new YyAppBar(this);
    // appBar所有按钮不可见
    d->_appBar->setWindowButtonFlags(YyAppBarType::NoneButtonHint);
    d->_appBar->setIsFixedSize(true);
    d->_appBar->setAppBarHeight(0);
#ifdef Q_OS_WIN
    // 防止意外拉伸
    createWinId();
#endif
    d->_leftButton = new YyPushButton("cancel", this);
    connect(d->_leftButton, &YyPushButton::clicked, this, [=]() {
        Q_EMIT leftButtonClicked();
        onLeftButtonClicked();
        d->_doCloseAnimation(false);
    });
    d->_leftButton->setMinimumSize(0, 0);
    d->_leftButton->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    d->_leftButton->setFixedHeight(38);
    d->_leftButton->setBorderRadius(6);
    d->_middleButton = new YyPushButton("minimum", this);
    connect(d->_middleButton, &YyPushButton::clicked, this, [=]() {
        Q_EMIT middleButtonClicked();
        onMiddleButtonClicked();
    });
    d->_middleButton->setMinimumSize(0, 0);
    d->_middleButton->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    d->_middleButton->setFixedHeight(38);
    d->_middleButton->setBorderRadius(6);
    d->_rightButton = new YyPushButton("exit", this);
    connect(d->_rightButton, &YyPushButton::clicked, this, [=]() {
        Q_EMIT rightButtonClicked();
        onRightButtonClicked(); //未实现
        d->_doCloseAnimation(true);
    });
    d->_rightButton->setLightDefaultColor(YyThemeColor(YyThemeType::Light, PrimaryNormal));
    d->_rightButton->setLightHoverColor(YyThemeColor(YyThemeType::Light, PrimaryHover));
    d->_rightButton->setLightPressColor(YyThemeColor(YyThemeType::Light, PrimaryPress));
    d->_rightButton->setLightTextColor(Qt::white);
    d->_rightButton->setDarkDefaultColor(YyThemeColor(YyThemeType::Dark, PrimaryNormal));
    d->_rightButton->setDarkHoverColor(YyThemeColor(YyThemeType::Dark, PrimaryHover));
    d->_rightButton->setDarkPressColor(YyThemeColor(YyThemeType::Dark, PrimaryPress));
    d->_rightButton->setDarkTextColor(Qt::black);
    d->_rightButton->setMinimumSize(0, 0);
    d->_rightButton->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    d->_rightButton->setFixedHeight(38);
    d->_rightButton->setBorderRadius(6);

    d->_centralWidget = new QWidget(this);
    QVBoxLayout* centralVLayout = new QVBoxLayout(d->_centralWidget);
    centralVLayout->setContentsMargins(15, 25, 15, 10);
    YyText* title = new YyText("退出", this);
    title->setTextStyle(YyTextType::Title);
    YyText* subTitle = new YyText("确定要退出程序吗", this);
    subTitle->setTextStyle(YyTextType::Body);
    centralVLayout->addWidget(title);
    centralVLayout->addSpacing(2);
    centralVLayout->addWidget(subTitle);
    centralVLayout->addStretch();

    d->_mainLayout = new QVBoxLayout(this);
    d->_mainLayout->setContentsMargins(0, 0, 0, 0);
    d->_buttonWidget = new QWidget(this);
    d->_buttonWidget->setFixedHeight(60);
    QHBoxLayout* buttonLayout = new QHBoxLayout(d->_buttonWidget);
    buttonLayout->addWidget(d->_leftButton);
    buttonLayout->addWidget(d->_middleButton);
    buttonLayout->addWidget(d->_rightButton);
    d->_mainLayout->addWidget(d->_centralWidget);
    d->_mainLayout->addWidget(d->_buttonWidget);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

YyContentDialog::~YyContentDialog()
{
    Q_D(YyContentDialog);
    d->_maskWidget->deleteLater();
}

void YyContentDialog::onLeftButtonClicked()
{
}

void YyContentDialog::onMiddleButtonClicked()
{
}

void YyContentDialog::onRightButtonClicked()
{
}

void YyContentDialog::setCentralWidget(QWidget* centralWidget)
{
    Q_D(YyContentDialog);
    d->_mainLayout->takeAt(0);
    d->_mainLayout->takeAt(0);
    delete d->_centralWidget;
    d->_centralWidget = centralWidget;
    d->_mainLayout->addWidget(centralWidget);
    d->_mainLayout->addWidget(d->_buttonWidget);
}

void YyContentDialog::setLeftButtonText(QString text)
{
    Q_D(YyContentDialog);
    d->_leftButton->setText(text);
}

void YyContentDialog::setMiddleButtonText(QString text)
{
    Q_D(YyContentDialog);
    d->_middleButton->setText(text);
}

void YyContentDialog::setRightButtonText(QString text)
{
    Q_D(YyContentDialog);
    d->_rightButton->setText(text);
}

void YyContentDialog::close()
{
    Q_D(YyContentDialog);
    d->_doCloseAnimation(false);
}

void YyContentDialog::showEvent(QShowEvent* event)
{
    Q_D(YyContentDialog);
    d->_maskWidget->setVisible(true);
    d->_maskWidget->raise();
    d->_maskWidget->setFixedSize(parentWidget()->size());
    d->_maskWidget->doMaskAnimation(90);
    QDialog::showEvent(event);
}

void YyContentDialog::paintEvent(QPaintEvent* event)
{
    Q_D(YyContentDialog);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(YyThemeColor(d->_themeMode, DialogBase));
    // 背景绘制
    painter.drawRect(rect());
    // 按钮栏背景绘制
    painter.setBrush(YyThemeColor(d->_themeMode, DialogLayoutArea));
    painter.drawRoundedRect(QRectF(0, height() - 60, width(), 60), 8, 8);
    painter.restore();
}

void YyContentDialog::keyPressEvent(QKeyEvent* event)
{
    event->accept();
}
