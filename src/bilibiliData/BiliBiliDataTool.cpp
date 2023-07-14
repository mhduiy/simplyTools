//
// Created by mhduiy on 2023/7/13.
//

#include "BiliBiliDataTool.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QStandardPaths>

BiliBiliDataTool::BiliBiliDataTool(QObject *parent) : QObject(parent) {
    jsonFilePath = qApp->applicationDirPath() + "/bilibili.json";
    manager = new QNetworkAccessManager;
}

QMap<int, QString> BiliBiliDataTool::getData() {
    QMap<int, QString> result;
    QString command = QString("python3") +
            " D:\\code\\simplyTools\\src\\customComponents\\res\\getBiliBiliData.py"
            + " " + sessdata + " " + bili_jct + " " + uid + " " + jsonFilePath;
    int ret = system(command.toLocal8Bit());

    // 读取json数据文件
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit readError("JSON file opening failed");
        return result;
    }
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (document.isNull()) {
        emit readError("json document is null");
        return result;
    }
    QJsonObject jsonObject = document.object();
    for(int i = 0; i < BL_TOTAL; i++) {
        if(jsonObject.contains(jsonKey.value(i))) {
            if(i == BL_iconUrl || i == BL_userName) {
                result.insert(i, jsonObject[jsonKey.value(i)].toString());
            }
            else if(i == BL_coinCount) {
                result.insert(i, QString::number(jsonObject[jsonKey.value(i)].toDouble()));
            }
            else {
                result.insert(i, QString::number(jsonObject[jsonKey.value(i)].toInt()));
            }
        }
    }
    file.close();
    qDebug() << file.remove();
    emit readFinish(result);    // 发送成功读取的消息
    return result;
}

void BiliBiliDataTool::getImageFromUrl(const QString &url) {
    // 设置要获取的图片链接
    QUrl imageUrl(url);

    // 发送网络请求获取图片
    QNetworkReply *reply = manager->get(QNetworkRequest(imageUrl));

    // 连接信号和槽，当请求完成时触发
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            // 读取图片数据
            QByteArray imageData = reply->readAll();

            // 将图片数据加载到 QPixmap
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            readUserImageFinish(pixmap);
        } else {
            // 处理请求错误
            qDebug() << "请求错误: " << reply->errorString();
        }

        // 清理资源
        reply->deleteLater();
    });
}

void BiliBiliDataTool::setData(const QString &_sessdata, const QString &_bili_jct, const QString &_uid) {
    this->sessdata = _sessdata;
    this->bili_jct = _bili_jct;
    this->uid = _uid;
}
