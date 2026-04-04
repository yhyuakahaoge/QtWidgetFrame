#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "YyWindow.h"
#include "YyContentDialog.h"
#include <QMainWindow>

class MainWindow : public YyWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    YyContentDialog* _closeDialog{nullptr};
};

#endif // MAINWINDOW_H
