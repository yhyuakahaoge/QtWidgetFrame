#include "YyNavigationBar.h"

#include "YyBaseListView.h"
// #include "YyFooterDelegate.h"
// #include "YyFooterModel.h"
#include "YyIconButton.h"
#include "YyInteractiveCard.h"
// #include "YyMenu.h"
// #include "YyNavigationModel.h"
// #include "YyNavigationNode.h"

// #include "YyNavigationView.h"
// #include "YySuggestBox.h"
#include "YyTheme.h"
// #include "YyToolButton.h"
#include "private/YyNavigationBarPrivate.h"
//#include "private/YySuggestBoxPrivate.h"
#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QScroller>
#include <QVBoxLayout>
Q_PROPERTY_CREATE_Q_CPP(YyNavigationBar, bool, IsTransparent)
// Q_PROPERTY_CREATE_Q_CPP(YyNavigationBar, bool, IsAllowPageOpenInNewWindow)
YyNavigationBar::YyNavigationBar(QWidget* parent)
    : QWidget{parent}, d_ptr(new YyNavigationBarPrivate())
{
    Q_D(YyNavigationBar);
    d->q_ptr = this;
    // d->_pIsAllowPageOpenInNewWindow = true;
    d->_pNavigationBarWidth = 300;
    setFixedWidth(300);
    d->_pIsTransparent = true;

    //用户卡片
    d->_userCard = new YyInteractiveCard(this);
    d->_userCard->setMinimumWidth(0);
    d->_userCard->setCardPixmap(QPixmap(":/include/Image/Cirno.jpg"));
    d->_userCard->setTitle("Yy Tool");
    d->_userCard->setSubTitle("6666666666@qq.com");
    // connect(d->_userCard, &YyInteractiveCard::clicked, this, &YyNavigationBar::userInfoCardClicked);
    d->_userButton = new YyIconButton(QPixmap(":/include/Image/Cirno.jpg"), this);
    d->_userButton->setFixedSize(36, 36);
    d->_userButton->setVisible(false);
    d->_userButton->setBorderRadius(8);
    d->_userButtonLayout = new QVBoxLayout();
    d->_userButtonLayout->setAlignment(Qt::AlignLeft);
    d->_userButtonLayout->setContentsMargins(0, 0, 0, 0);
    d->_userButtonLayout->setSpacing(0);
    d->_userButtonLayout->addWidget(d->_userButton);

    // connect(d->_userButton, &YyIconButton::clicked, this, &YyNavigationBar::userInfoCardClicked);
    d->_userCardLayout = new QVBoxLayout();
    d->_userCardLayout->setContentsMargins(3, 10, 0, 5);
    d->_userCardLayout->addLayout(d->_userButtonLayout);
    d->_userCardLayout->addWidget(d->_userCard);

    // // 搜索跳转
    // //    connect(d->_navigationSuggestBox, &YySuggestBox::suggestionClicked, this, [=](QString suggestText, QVariantMap suggestData) {
    // //        navigation(suggestData.value("YyPageKey").toString());
    // //    });

    // // 导航模型
    // d->_navigationModel = new YyNavigationModel(this);
    // d->_navigationView = new YyNavigationView(this);
    // d->_navigationView->setNavigationBarPrivate(d);
    // d->_navigationView->setModel(d->_navigationModel);
    // connect(d->_navigationView, &YyNavigationView::navigationClicked, this, [=](const QModelIndex& index) {
    //     d->onTreeViewClicked(index);
    // });
    // connect(d->_navigationView, &YyNavigationView::navigationOpenNewWindow, d, &YyNavigationBarPrivate::onNavigationOpenNewWindow);

    // // 页脚
    // d->_footerView = new YyBaseListView(this);
    // d->_footerView->setFixedHeight(0);
    // d->_footerModel = new YyFooterModel(this);
    // d->_footerView->setModel(d->_footerModel);
    // d->_footerDelegate = new YyFooterDelegate(this);
    // d->_footerDelegate->setYyListView(d->_footerView);
    // d->_footerView->setItemDelegate(d->_footerDelegate);
    // connect(d->_footerView, &YyBaseListView::mousePress, this, [=](const QModelIndex& index) {
    //     d->_footerDelegate->setPressIndex(index);
    //     d->_footerView->viewport()->update();
    // });
    // connect(d->_footerView, &YyBaseListView::mouseDoubleClick, this, [=](const QModelIndex& index) {
    //     d->_footerDelegate->setPressIndex(index);
    //     d->_footerView->viewport()->update();
    // });
    // connect(d->_footerView, &YyBaseListView::mouseRelease, this, [=](const QModelIndex& index) {
    //     d->_footerDelegate->setPressIndex(QModelIndex());
    //     d->_footerView->viewport()->update();
    // });
    // connect(d->_footerView, &YyBaseListView::clicked, this, [=](const QModelIndex& index) {
    //     d->onFooterViewClicked(index);
    // });

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setSpacing(0);
    //mainLayout->addLayout(d->_userCardLayout);

    //mainLayout->addWidget(d->_navigationView);
    //mainLayout->addWidget(d->_footerView);

    // // 主题设置
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, this, [=](YyThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

YyNavigationBar::~YyNavigationBar()
{
}

void YyNavigationBar::setNavigationBarWidth(int navigationBarWidth)
{
    Q_D(YyNavigationBar);
    if (navigationBarWidth < 180)
    {
        navigationBarWidth = 180;
    }
    if (d->_currentDisplayMode == YyNavigationType::NavigationDisplayMode::Maximal)
    {
        setFixedWidth(navigationBarWidth);
    }
    d->_pNavigationBarWidth = navigationBarWidth;
    Q_EMIT pNavigationBarWidthChanged();
}

int YyNavigationBar::getNavigationBarWidth() const
{
    Q_D(const YyNavigationBar);
    return d->_pNavigationBarWidth;
}

void YyNavigationBar::setUserInfoCardVisible(bool isVisible)
{
    Q_D(YyNavigationBar);
    d->_isShowUserCard = isVisible;
    if (d->_currentDisplayMode == YyNavigationType::NavigationDisplayMode::Compact)
    {
        d->_userButton->setVisible(isVisible);
    }
    else
    {
        d->_userCard->setVisible(isVisible);
    }
    if (isVisible)
    {
        d->_userCardLayout->setContentsMargins(3, 10, 5, 5);
    }
    else
    {
        d->_userCardLayout->setContentsMargins(0, 0, 0, 0);
    }
}

void YyNavigationBar::setUserInfoCardPixmap(QPixmap pix)
{
    Q_D(YyNavigationBar);
    d->_userCard->setCardPixmap(pix);
    d->_userButton->setPixmap(pix);
}

void YyNavigationBar::setUserInfoCardTitle(QString title)
{
    Q_D(YyNavigationBar);
    d->_userCard->setTitle(title);
}

void YyNavigationBar::setUserInfoCardSubTitle(QString subTitle)
{
    Q_D(YyNavigationBar);
    d->_userCard->setSubTitle(subTitle);
}


void YyNavigationBar::paintEvent(QPaintEvent* event)
{
    Q_D(YyNavigationBar);
    if (!d->_pIsTransparent)
    {
        QPainter painter(this);
        painter.save();
        painter.setPen(YyThemeColor(d->_themeMode, PopupBorder));
        painter.setBrush(YyThemeColor(d->_themeMode, PopupBase));
        QRect baseRect = this->rect();
        baseRect.adjust(-1, 0, -1, 0);
        QPainterPath path;
        path.moveTo(baseRect.topLeft());
        path.lineTo(QPoint(baseRect.right() - 8, baseRect.y()));
        path.arcTo(QRectF(baseRect.right() - 16, baseRect.y(), 16, 16), 90, -90);
        path.lineTo(QPoint(baseRect.right(), baseRect.bottom() - 8));
        path.arcTo(QRectF(baseRect.right() - 16, baseRect.bottom() - 16, 16, 16), 0, -90);
        path.lineTo(baseRect.bottomLeft());
        path.closeSubpath();
        painter.drawPath(path);
        painter.restore();
    }
    QWidget::paintEvent(event);
}
