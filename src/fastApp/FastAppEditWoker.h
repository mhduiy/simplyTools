#ifndef FASTAPPEditWOKER_H
#define FASTAPPEditWOKER_H

#include <QObject>
#include <dtkwidget_global.h>
#include <qobjectdefs.h>
#include <DDialog>

DWIDGET_USE_NAMESPACE

enum SettingType {DBUS, APP};

struct SettingInfo {
    SettingType type;

    QString headIconPath;
    QString headTitleName;

    QString appPath;
    QStringList args;

    QString dbusInterface;
};

class FastAppEditWorker : public QObject{
    Q_OBJECT
public:
    void editFastAppInfo(int id);
    void addFastAppInfo(int id);
private:
    
};

#endif