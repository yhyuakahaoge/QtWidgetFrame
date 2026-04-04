#ifndef YySTATUSBAR_H
#define YySTATUSBAR_H

#include <QStatusBar>

#include "YyProperty.h"
class Yy_EXPORT YyStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit YyStatusBar(QWidget* parent = nullptr);
    ~YyStatusBar() override;
};

#endif // YySTATUSBAR_H
