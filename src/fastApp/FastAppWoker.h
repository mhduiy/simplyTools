#ifndef FASTAPPWOKER_H
#define FASTAPPWOKER_H

#include <QObject>
#include <QStackedWidget>
#include "customComponents/MDialog.h"
#include "customComponents/MLineEdit.h"
#include "customComponents/MTabSwitchButton.h"

enum SettingType {DBUS, APP};

struct SettingInfo {
    SettingType type;

    QString headIconPath;
    QString headTitleName;

    QString appPath;
    QStringList args;

    QString dbusInterface;
};

class FastAppWorker : public QObject{
    Q_OBJECT
public:
    explicit FastAppWorker(QObject *parent = nullptr);
    void editFastAppInfo(int id);
    void addFastAppInfo(int id);
    void showDialog();
private:
    MDialog *m_dialog = nullptr;

    QWidget *m_dialogWidget = nullptr;
    MTabSwitchButton *m_tabSwitchButton = nullptr;

    QLabel *m_appIcon = nullptr;
    MLineEdit *m_appNameEdit = nullptr;
    MLineEdit *m_appDescribtionEdit = nullptr;

    QWidget *m_appWidget = nullptr;
    MLineEdit *m_appPathEdit = nullptr;
    MLineEdit *m_appArgsEdit = nullptr;

    QWidget *m_cmdWidget = nullptr;
    MLineEdit *m_cmdEdit = nullptr;

    QWidget *m_dbusWidget = nullptr;

    QStackedWidget *m_stackedWidget = nullptr;
};

#endif