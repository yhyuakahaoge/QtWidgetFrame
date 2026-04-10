#ifndef YySUGGESTBOXPRIVATE_H
#define YySUGGESTBOXPRIVATE_H

#include <QAction>
#include <QObject>
#include <QSize>
#include <QVariantMap>
#include <QVector>

#include "YyDef.h"
class YySuggestion : public QObject
{
    Q_OBJECT
    Q_PROPERTY_CREATE(YyIconType::IconName, YyIcon)
    Q_PROPERTY_CREATE(QString, SuggestText)
    Q_PROPERTY_CREATE(QString, SuggestKey)
    Q_PROPERTY_CREATE(QVariantMap, SuggestData)
public:
    explicit YySuggestion(QObject* parent = nullptr);
    ~YySuggestion() override;
};

class QVBoxLayout;
class YyLineEdit;
class YyNavigationNode;
class YySuggestModel;
class YyBaseListView;
class YySuggestDelegate;
class YySuggestBox;
class YySuggestBoxSearchViewContainer;
class YySuggestBoxPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(YySuggestBox)
    Q_PROPERTY_CREATE_D(int, BorderRadius)
    Q_PROPERTY_CREATE_D(Qt::CaseSensitivity, CaseSensitivity)
public:
    explicit YySuggestBoxPrivate(QObject* parent = nullptr);
    ~YySuggestBoxPrivate();
    Q_SLOT void onThemeModeChanged(YyThemeType::ThemeMode themeMode);
    Q_SLOT void onSearchEditTextEdit(const QString& searchText);
    Q_SLOT void onSearchViewClicked(const QModelIndex& index);

private:
    YyThemeType::ThemeMode _themeMode;
    QAction* _lightSearchAction{nullptr};
    QAction* _darkSearchAction{nullptr};
    QVector<YySuggestion*> _suggestionVector;
    YySuggestBoxSearchViewContainer* _searchViewBaseWidget{nullptr};
    YyLineEdit* _searchEdit{nullptr};
    YySuggestModel* _searchModel{nullptr};
    YyBaseListView* _searchView{nullptr};
    YySuggestDelegate* _searchDelegate{nullptr};
    QVBoxLayout* _shadowLayout{nullptr};
    QSize _lastSize;
    bool _isExpandAnimationFinished{true};
    bool _isCloseAnimationFinished{true};
    void _startSizeAnimation(QSize oldSize, QSize newSize);
    void _startExpandAnimation();
    void _startCloseAnimation();
};

#endif // YySUGGESTBOXPRIVATE_H
