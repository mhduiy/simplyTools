#include "TranslateTool.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QApplication>
#include "global/globalSetting.h"


TranslateTool::TranslateTool(QObject *parent) : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager;
}

void TranslateTool::TranslateFromBaidu(QString src, QString from, QString to, bool finishExit)
{
    //按照 appid+q+salt+密钥的顺序拼接得到字符串 1。
    auto globalSettingInstance = globalSetting::getInstance();
    QString MY_APID;
    QString MY_APID_KEY;
    if(globalSettingInstance) {
        MY_APID = globalSettingInstance->readConfig("simplyTranslate", "appId");
        MY_APID_KEY = globalSettingInstance->readConfig("simplyTranslate", "appKey");
    }
    if(MY_APID.isEmpty() || MY_APID_KEY.isEmpty()) {
        emit disMsgAppend("翻译错误: 没有设置API");
        qWarning() << "翻译错误: 没有设置API";
        if (finishExit) {
            qApp->processEvents();
            qApp->exit(0);
        }
        return;
    }
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

    qWarning() << "翻译中..." << from << to << src;
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
            int errorCode = jsonObject.value("error_code").toString().toInt();
            QString errorStr = getError(errorCode);
            emit disMsgAppend("翻译错误: " + errorStr);
            qWarning() << "翻译错误: " + errorStr;
            if (finishExit) {
                qApp->processEvents();
                qApp->exit(0);
            }
            return;
        }
        QJsonValue locationArray = locationValueArray.at(0);
        QJsonObject location = locationArray.toObject();
        QString toMsg = location["dst"].toString();

        //返回内容
        qInfo() << toMsg;
        emit translateOK(toMsg);
        reply->close();
        reply->deleteLater();
        if (finishExit) {
            qApp->processEvents();
            qApp->exit(0);
        }
    });
}

QString TranslateTool::getError(const int code)
{
    QString errorStr;
    switch (code) {
    case 52001: {
        errorStr = "请求超时";
        break;
    }
    case 52002: {
        errorStr = "系统错误";
        break;
    }
    case 52003: {
        errorStr = "未授权用户, 检查API是否正确设置";
        break;
    }
    case 54000: {
        errorStr = "必填参数为空";
        break;
    }
    case 54001: {
        errorStr = "签名错误";
        break;
    }
    case 54003: {
        errorStr = "访问频率受限";
        break;
    }
    case 54004: {
        errorStr = "账户余额不足";
        break;
    }
    case 54005: {
        errorStr = "长query请求频繁";
        break;
    }
    case 58000: {
        errorStr = "客户端IP非法";
        break;
    }
    case 58001: {
        errorStr = "译文语言方向不支持";
        break;
    }
    case 58002: {
        errorStr = "服务当前已关闭";
        break;
    }
    case 90107: {
        errorStr = "认证未通过或未生效";
        break;
    }
    default:{
        errorStr = "code: " + QString::number(code);
    }
}
return errorStr;
}