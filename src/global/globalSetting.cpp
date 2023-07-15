//
// Created by mhduiy on 2023/7/15.
//

#include <QStandardPaths>
#include <QDir>
#include "globalSetting.h"
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

globalSetting* globalSetting::instance = nullptr;

globalSetting::globalSetting(QObject *parent) : QObject(parent) {
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    qDebug() << cacheDir;
    // 创建目录
    QDir dir(cacheDir);
    if(!dir.exists(cacheDir)) {
        dir.mkpath(cacheDir);
    }
    settings = new QSettings(cacheDir + "/config.ini", QSettings::IniFormat);
}

void globalSetting::writeConfig(const QString &title, const QString &key, const QString &value) {
    settings->setValue(QString("%1/%2").arg(title, key), value);
}

QString globalSetting::readConfig(const QString &title, const QString &key) {
    return settings->value(QString("%1/%2").arg(title, key), "").toString();
}

globalSetting *globalSetting::getInstance(QObject *parent) {
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if(instance == nullptr) {
        instance = new globalSetting(parent);
    }
    return instance;
}
