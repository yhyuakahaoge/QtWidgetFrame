#ifndef YySUGGESTBOX_H
#define YySUGGESTBOX_H

#include <QVariantMap>
#include <QWidget>

#include "YyDef.h"
#include "YyProperty.h"

class YySuggestBoxPrivate;
class Yy_EXPORT YySuggestBox : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(YySuggestBox)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
    Q_PROPERTY_CREATE_Q_H(Qt::CaseSensitivity, CaseSensitivity)
public:
    explicit YySuggestBox(QWidget* parent = nullptr);
    ~YySuggestBox() override;
    void setPlaceholderText(const QString& placeholderText);
    void setFixedSize(const QSize& size);
    void setFixedSize(int w, int h);
    void setFixedHeight(int h);

    struct Yy_EXPORT SuggestData {
        Q_PRIVATE_CREATE(YyIconType::IconName, YyIcon)
        Q_PRIVATE_CREATE(QString, SuggestText)
        Q_PRIVATE_CREATE(QString, SuggestKey)
        Q_PRIVATE_CREATE(QVariantMap, SuggestData)
    public:
        explicit SuggestData();
        explicit SuggestData(YyIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData = {});
        ~SuggestData();
    };
    QString addSuggestion(const QString& suggestText, const QVariantMap& suggestData = {});
    QString addSuggestion(YyIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData = {});
    QString addSuggestion(const YySuggestBox::SuggestData& suggestData);
    QStringList addSuggestion(const QList<YySuggestBox::SuggestData>& suggestDataList);

    void removeSuggestion(const QString& suggestKey);
    void removeSuggestion(int index);
    void clearSuggestion();
Q_SIGNALS:
    Q_SIGNAL void suggestionClicked(const YySuggestBox::SuggestData& suggestData);
};

#endif // YySUGGESTBOX_H
