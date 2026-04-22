#ifndef YyBASELISTVIEW_H
#define YyBASELISTVIEW_H

#include <QListView>
#include <QModelIndex>

class YyScrollBar;
class YyBaseListView : public QListView
{
    Q_OBJECT
public:
    explicit YyBaseListView(QWidget* parent = nullptr);
    ~YyBaseListView();
Q_SIGNALS:
    Q_SIGNAL void mousePress(const QModelIndex& index);
    Q_SIGNAL void mouseRelease(const QModelIndex& index);
    Q_SIGNAL void mouseDoubleClick(const QModelIndex& index);

protected:
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // YyBASELISTVIEW_H
