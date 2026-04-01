#ifndef YyMENU_H
#define YyMENU_H

#include <QMenu>
#include <QWidget>

#include "YyDef.h"
#include "YyProperty.h"
class YyMenuPrivate;
class Yy_EXPORT YyMenu : public QMenu
{
    Q_OBJECT
    Q_Q_CREATE(YyMenu)

public:
    explicit YyMenu(QWidget* parent = nullptr);
    explicit YyMenu(const QString& title, QWidget* parent = nullptr);
    ~YyMenu();
    void setMenuItemHeight(int menuItemHeight);
    int getMenuItemHeight() const;

    QAction* addMenu(QMenu* menu);
    YyMenu* addMenu(const QString& title);
    YyMenu* addMenu(const QIcon& icon, const QString& title);
    YyMenu* addMenu(YyIconType::IconName icon, const QString& title);

    QAction* addYyIconAction(YyIconType::IconName icon, const QString& text);
    QAction* addYyIconAction(YyIconType::IconName icon, const QString& text, const QKeySequence& shortcut);

    bool isHasChildMenu() const;
    bool isHasIcon() const;
Q_SIGNALS:
    Q_SIGNAL void menuShow();

protected:
    virtual void showEvent(QShowEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // YyMENU_H
