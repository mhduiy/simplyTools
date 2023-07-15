//
// Created by mhduiy on 2023/7/15.
//

#ifndef SIMPLYTOOLS_GLOBALSETTING_H
#define SIMPLYTOOLS_GLOBALSETTING_H

#include <QObject>
#include <QSettings>

class globalSetting : public QObject{
Q_OBJECT
public:
    void writeConfig(const QString& title, const QString& key, const QString &value);
    QString readConfig(const QString& title, const QString& key);
    static globalSetting* getInstance(QObject *parent = nullptr);
private:
    static globalSetting *instance;
    explicit globalSetting(QObject *parent = nullptr);
    QSettings *settings = nullptr;
};


#endif //SIMPLYTOOLS_GLOBALSETTING_H
