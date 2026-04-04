#include "YyContentDialogPrivate.h"

#include "YyContentDialog.h"
#include "YyMaskWidget.h"
YyContentDialogPrivate::YyContentDialogPrivate(QObject* parent)
    : QObject{parent}
{
}

YyContentDialogPrivate::~YyContentDialogPrivate()
{
}

void YyContentDialogPrivate::_doCloseAnimation(bool isAccept)
{
    Q_Q(YyContentDialog);
    _maskWidget->doMaskAnimation(0);
    isAccept ? q->accept() : q->reject();
}
