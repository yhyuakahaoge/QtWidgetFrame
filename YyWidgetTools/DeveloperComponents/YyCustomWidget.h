#ifndef YyCUSTOMWIDGET_H
#define YyCUSTOMWIDGET_H

#include <QDialog>

#include "YyAppBar.h"
#include "YyDef.h"

class QVBoxLayout;
class YyCustomWidget : public QDialog
{
    Q_OBJECT
    Q_TAKEOVER_NATIVEEVENT_H
public:
    explicit YyCustomWidget(QWidget* parent = nullptr);
    virtual ~YyCustomWidget() override;

    void setCentralWidget(QWidget* widget);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    QVBoxLayout* _mainLayout{nullptr};
    YyAppBar* _appBar{nullptr};
    QWidget* _centralWidget{nullptr};

private:
    YyThemeType::ThemeMode _themeMode;
    YyApplicationType::WindowDisplayMode _windowDisplayMode;
};

#endif // YyCUSTOMWIDGET_H
