#ifndef YyMICABASEINITOBJECT_H
#define YyAMICABASEINITOBJECT_H

#include <QObject>
class YyApplicationPrivate;
class YyMicaBaseInitObject : public QObject
{
    Q_OBJECT
public:
    explicit YyMicaBaseInitObject(YyApplicationPrivate* appPrivate, QObject* parent = nullptr);
    ~YyMicaBaseInitObject();
    Q_SLOT void onInitMicaBase(QImage img);
Q_SIGNALS:
    Q_SIGNAL void initFinished();

private:
    YyApplicationPrivate* _appPrivate{nullptr};
};

#endif // YyMICABASEINITOBJECT_H
