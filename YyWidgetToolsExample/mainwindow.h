#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "YyWindow.h"
#include <QMainWindow>

class YySuggestBox;
class YyContentDialog;
class MainWindow : public YyWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

    void initWindow();
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    YyContentDialog* _closeDialog{nullptr};
    YySuggestBox* _windowSuggestBox{nullptr};
};

#endif // MAINWINDOW_H
