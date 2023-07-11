#ifndef TRANSLATETOOL_H
#define TRANSLATETOOL_H

#include <QNetworkAccessManager>
#include <QObject>

class TranslateTool : public QObject
{
Q_OBJECT
public:
    explicit TranslateTool(QObject *parent = nullptr);

    void TranslateFromBaidu(QString src, QString from, QString to);


signals:
    void translateOK(QString to);

    void disMsgAppend(QString msg);

private:
    QNetworkAccessManager *m_networkAccessManager;

public slots:
};

#endif // TRANSLATETOOL_H
