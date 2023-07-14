//
// Created by mhduiy on 2023/7/13.
//

#ifndef SIMPLYTOOLS_BILIBILIDATATOOL_H
#define SIMPLYTOOLS_BILIBILIDATATOOL_H

#include <QObject>
#include <QMap>
#include <QGuiApplication>
#include <QNetworkAccessManager>

const QString pythonFileName = ":/getBiliBiliData.py";

enum bilibiliDataEnum {
    BL_iconUrl = 0,
    BL_userName,
    BL_uid,
    BL_level,
    BL_coinCount,
    BL_followCount,
    BL_fansCount,
    BL_likeCount,
    BL_playCount,
    BL_readCount,
    BL_TOTAL
};

const QStringList jsonKey {
    "iconUrl",
    "userName",
    "uid",
    "level",
    "coinCount",
    "followCount",
    "fansCount",
    "likeCount",
    "playCount",
    "readCount"
};

class BiliBiliDataTool : public QObject{
    Q_OBJECT
public:
    explicit BiliBiliDataTool(QObject *parent = nullptr);
    QMap<int, QString> getData();
    void getImageFromUrl(const QString &url);

    void setData(const QString &sessdata, const QString &bili_jct, const QString &uid);

signals:

    void readFinish(const QMap<int, QString>& map);
    void readError(const QString& errorInfo);
    void readUserImageFinish(const QPixmap &pixmap);

private:
    QString jsonFilePath;
    QNetworkAccessManager *manager = nullptr;

    QString sessdata;
    QString bili_jct;
    QString uid;
};


#endif //SIMPLYTOOLS_BILIBILIDATATOOL_H
