#ifndef YyNAVIGATIONVIEW_H
#define YyNAVIGATIONVIEW_H

#include "YyDef.h"
#include "YyNavigationBarPrivate.h"
#include <QObject>
#include <QTreeView>
class YyScrollBar;
class YyNavigationStyle;
class YyToolTip;
class YyNavigationView : public QTreeView
{
    Q_OBJECT
    Q_PRIVATE_CREATE(const YyNavigationBarPrivate*, NavigationBarPrivate)
public:
    explicit YyNavigationView(QWidget* parent = nullptr);
    ~YyNavigationView() override;
    void navigationNodeStateChange(QVariantMap data);

    Q_SLOT void onCustomContextMenuRequested(const QPoint& pos);
Q_SIGNALS:
    Q_SIGNAL void navigationClicked(const QModelIndex& index);
    Q_SIGNAL void navigationOpenNewWindow(QString nodeKey);

protected:
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    YyNavigationStyle* _navigationStyle{nullptr};
    YyToolTip* _compactToolTip{nullptr};
    void _doCompactToolTip();
};

#endif // YyNAVIGATIONVIEW_H
