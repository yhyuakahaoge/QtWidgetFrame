#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "YyWindow.h"
#include <QMainWindow>

class MainWindow : public YyWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

};

#endif // MAINWINDOW_H
