#include "Translatetool.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>



TranslateTool::TranslateTool(QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager;
}

void TranslateTool::TranslateFromBaidu(QString src, QString from, QString to)
{
    //按照 appid+q+salt+密钥的顺序拼接得到字符串 1。
    QString MY_APID = "20220509001209732";
    QString MY_APID_KEY = "G8FLi63QsAvBtbogp7Ra";
    QString baseUrl = "https://fanyi-api.baidu.com/api/trans/vip/translate?";

    //生成md5加密文件
    char salt[60];
    sprintf(salt,"%d",rand());
    QString sign=QString("%1%2%3%4").arg(MY_APID).arg(src).arg(salt).arg(MY_APID_KEY);
    QByteArray str = QCryptographicHash::hash(sign.toUtf8(),QCryptographicHash::Md5);
    QString MD5=str.toHex();

    QString sUrl = baseUrl + QString("q=%1&from=%2&to=%3&appid=%4""&salt=%5&sign=%6")
            .arg(src).arg(from).arg(to).arg(MY_APID).arg(salt).arg(MD5);//
    QUrl url(sUrl);
    QNetworkRequest request(url);

    QNetworkReply *reply = m_networkAccessManager->get(request);//send GET request to get result

    /* return data */
    connect(reply, &QNetworkReply::readyRead, [=]{
        QByteArray data = reply->readAll();
        //json解析
        QJsonDocument m_document;
        m_document = QJsonDocument::fromJson(data);

        QJsonObject jsonObject = m_document.object();
        QJsonValue locationValue = jsonObject.value(QStringLiteral("trans_result"));
        QJsonArray locationValueArray = locationValue.toArray();

        if(locationValueArray.empty())
        {
            emit disMsgAppend("翻译错误:"+data);
            return;
        }
        QJsonValue locationArray = locationValueArray.at(0);
        QJsonObject location = locationArray.toObject();
        QString toMsg = location["dst"].toString();

        //返回内容
        emit translateOK(toMsg);
        reply->close();
    });

}
