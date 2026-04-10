#include "YySuggestBox.h"

#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QMap>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>

#include "YyBaseListView.h"
#include "YyIcon.h"
//#include "YyLineEdit.h"
//#include "YyScrollBar.h"
//#include "YySuggestBoxSearchViewContainer.h"
//#include "YySuggestDelegate.h"
//#include "YySuggestModel.h"
#include "YyTheme.h"
#include "private/YySuggestBoxPrivate.h"

Q_PROPERTY_CREATE_Q_CPP(YySuggestBox, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(YySuggestBox, Qt::CaseSensitivity, CaseSensitivity)
YySuggestBox::SuggestData::SuggestData()
{
}

YySuggestBox::SuggestData::SuggestData(YyIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData)
    : _pYyIcon(icon), _pSuggestText(suggestText), _pSuggestData(suggestData)
{
}

YySuggestBox::SuggestData::~SuggestData()
{
}

YySuggestBox::YySuggestBox(QWidget* parent)
    : QWidget{parent}, d_ptr(new YySuggestBoxPrivate())
{
    Q_D(YySuggestBox);
    QWidget::setFixedSize(280, 35);
    d->q_ptr = this;
    d->_pBorderRadius = 6;
    d->_pCaseSensitivity = Qt::CaseInsensitive;
    // d->_searchEdit = new YyLineEdit(this);
    // d->_searchEdit->setFixedHeight(35);
    // d->_searchEdit->setPlaceholderText("查找功能");
    // d->_searchEdit->setClearButtonEnabled(true);
    d->_lightSearchAction = new QAction(YyIcon::getInstance()->getYyIcon(YyIconType::MagnifyingGlass), "Search", this);
    d->_darkSearchAction = new QAction(YyIcon::getInstance()->getYyIcon(YyIconType::MagnifyingGlass, QColor(0xFF, 0xFF, 0xFF)), "Search", this);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &YyTheme::themeModeChanged, d, &YySuggestBoxPrivate::onThemeModeChanged);
    if (d->_themeMode == YyThemeType::Light)
    {
        //d->_searchEdit->addAction(d->_lightSearchAction, QLineEdit::TrailingPosition);
    }
    else
    {
       // d->_searchEdit->addAction(d->_darkSearchAction, QLineEdit::TrailingPosition);
    }

    connect(d->_lightSearchAction, &QAction::triggered, this, [=](bool checked) {
        //qDebug() << "Search";
    });

    connect(d->_darkSearchAction, &QAction::triggered, this, [=](bool checked) {
        //qDebug() << "Search";
    });
    // QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // mainLayout->setSpacing(0);
    // mainLayout->setContentsMargins(0, 0, 0, 0);
    // mainLayout->addWidget(d->_searchEdit);
    // d->_searchViewBaseWidget = new YySuggestBoxSearchViewContainer(window());
    // d->_shadowLayout = new QVBoxLayout(d->_searchViewBaseWidget);
    // d->_shadowLayout->setContentsMargins(0, 0, 0, 0);
    // d->_searchView = new YyBaseListView(d->_searchViewBaseWidget);
    // YyScrollBar* floatVScrollBar = new YyScrollBar(d->_searchView->verticalScrollBar(), d->_searchView);
    // floatVScrollBar->setIsAnimation(true);
    // d->_searchViewBaseWidget->resize(292, 300);
    // d->_shadowLayout->addWidget(d->_searchView);
    // d->_searchModel = new YySuggestModel(this);
    // d->_searchDelegate = new YySuggestDelegate(this);
    // d->_searchView->setModel(d->_searchModel);
    // d->_searchView->setItemDelegate(d->_searchDelegate);
    // d->_searchViewBaseWidget->hide();
    // connect(d->_searchEdit, &YyLineEdit::textEdited, d, &YySuggestBoxPrivate::onSearchEditTextEdit);
    // connect(d->_searchEdit, &YyLineEdit::focusIn, d, &YySuggestBoxPrivate::onSearchEditTextEdit);
    // connect(d->_searchView, &YyBaseListView::clicked, d, &YySuggestBoxPrivate::onSearchViewClicked);

    // // 焦点事件
    // connect(d->_searchEdit, &YyLineEdit::wmFocusOut, this, [=]() {
    //     if (!d->_searchView->underMouse())
    //     {
    //         d->_startCloseAnimation();
    //     }
    // });
}

YySuggestBox::~YySuggestBox()
{
}

void YySuggestBox::setPlaceholderText(const QString& placeholderText)
{
   // Q_D(YySuggestBox);
  //  d->_searchEdit->setPlaceholderText(placeholderText);
}

void YySuggestBox::setFixedSize(const QSize& size)
{
  //  Q_D(YySuggestBox);
  //  d->_searchEdit->setFixedHeight(size.height());
  //  QWidget::setFixedSize(size);
}
void YySuggestBox::setFixedSize(int w, int h)
{
  //  Q_D(YySuggestBox);
    //d->_searchEdit->setFixedHeight(h);
  //  QWidget::setFixedSize(w, h);
}
void YySuggestBox::setFixedHeight(int h)
{
 //   Q_D(YySuggestBox);
  //  d->_searchEdit->setFixedHeight(h);
  //  QWidget::setFixedHeight(h);
}

QString YySuggestBox::addSuggestion(const QString& suggestText, const QVariantMap& suggestData)
{
    Q_D(YySuggestBox);
    YySuggestion* suggest = new YySuggestion(this);
    suggest->setSuggestText(suggestText);
    suggest->setSuggestData(suggestData);
    d->_suggestionVector.append(suggest);
    return suggest->getSuggestKey();
}

QString YySuggestBox::addSuggestion(YyIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData)
{
    Q_D(YySuggestBox);
    YySuggestion* suggest = new YySuggestion(this);
    suggest->setYyIcon(icon);
    suggest->setSuggestText(suggestText);
    suggest->setSuggestData(suggestData);
    d->_suggestionVector.append(suggest);
    return suggest->getSuggestKey();
}

QString YySuggestBox::addSuggestion(const YySuggestBox::SuggestData& suggestData)
{
    Q_D(YySuggestBox);
    YySuggestion* suggest = new YySuggestion(this);
    suggest->setYyIcon(suggestData.getYyIcon());
    suggest->setSuggestText(suggestData.getSuggestText());
    suggest->setSuggestData(suggestData.getSuggestData());
    d->_suggestionVector.append(suggest);
    return suggest->getSuggestKey();
}

QStringList YySuggestBox::addSuggestion(const QList<YySuggestBox::SuggestData>& suggestDataList)
{
    Q_D(YySuggestBox);
    QStringList suggestKeyList;
    for (const auto& suggestData: suggestDataList)
    {
        YySuggestion* suggest = new YySuggestion(this);
        suggest->setYyIcon(suggestData.getYyIcon());
        suggest->setSuggestText(suggestData.getSuggestText());
        suggest->setSuggestData(suggestData.getSuggestData());
        d->_suggestionVector.append(suggest);
        suggestKeyList.append(suggest->getSuggestKey());
    }
    return suggestKeyList;
}

void YySuggestBox::removeSuggestion(const QString& suggestKey)
{
    Q_D(YySuggestBox);
    foreach (auto suggest, d->_suggestionVector)
    {
        if (suggest->getSuggestKey() == suggestKey)
        {
     //       d->_suggestionVector.removeOne(suggest);
      //      suggest->deletYyter();
        }
    }
}

void YySuggestBox::removeSuggestion(int index)
{
    Q_D(YySuggestBox);
    if (index >= d->_suggestionVector.count())
    {
        return;
    }
    YySuggestion* suggest = d->_suggestionVector[index];
    d->_suggestionVector.removeOne(suggest);
  //  suggest->deletYyter();
}

void YySuggestBox::clearSuggestion()
{
    Q_D(YySuggestBox);
    foreach (auto suggest, d->_suggestionVector)
    {
    //    d->_suggestionVector.removeOne(suggest);
    //    suggest->deletYyter();
    }
}
