//
// Created by mhduiy on 2023/7/11.
//

#include "simplyTranslateWidget.h"
#include <QLayout>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QFile>
#include <QNetworkConfigurationManager>
#include "global/globalSetting.h"

simplyTranslateWidget::simplyTranslateWidget(QWidget *parent) : QWidget(parent){
    initUI();

    // 加载样式表
    QFile file(":/translate.qss");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        this->setStyleSheet(file.readAll());
    }
    file.close();
}

void simplyTranslateWidget::initUI() {
    translatetool = new TranslateTool(this);
    tranFromBox = new QGroupBox();
    tranToBox = new QGroupBox();
    ed_tranFrom = new QTextEdit();
    ed_tranTo = new QTextEdit();

    srcTypeBox = new QComboBox();
    tarTypeBox = new QComboBox();
    exchangeBtn = new MButton();
    setUserInfoBtn = new MButton("设置api信息");

    exchangeBtn->setIcon(QIcon(":/exchangeIcon.png"));

    pasteBtn = new MButton("从剪切板粘贴");
    tranBtn = new MButton("翻译");
    clearBtn = new MButton("清除内容");
    copyBtn = new MButton("复制翻译结果");

    exchangeBtn->setFixedSize(36,36);
    srcTypeBox->setFixedHeight(36);
    tarTypeBox->setFixedHeight(36);

    auto *mainLayout = new QVBoxLayout(this);
    auto *topOperatorLayout = new QHBoxLayout();
    auto *bottomOperatorLayout = new QHBoxLayout();

    topOperatorLayout->addWidget(srcTypeBox);
    topOperatorLayout->addWidget(exchangeBtn);
    topOperatorLayout->addWidget(tarTypeBox);
    topOperatorLayout->addWidget(tranBtn);
    topOperatorLayout->addWidget(pasteBtn);

    bottomOperatorLayout->addWidget(setUserInfoBtn);
    bottomOperatorLayout->addWidget(clearBtn);
    bottomOperatorLayout->addWidget(copyBtn);

    mainLayout->addLayout(topOperatorLayout);
    mainLayout->addWidget(tranFromBox);
    mainLayout->addWidget(tranToBox);
    mainLayout->addLayout(bottomOperatorLayout);

    tranFromBox->setLayout(new QVBoxLayout);
    tranFromBox->layout()->addWidget(ed_tranFrom);
    tranToBox->setLayout(new QVBoxLayout);
    tranToBox->layout()->addWidget(ed_tranTo);

    tranFromBox->setTitle("输入需要翻译的内容");
    tranToBox->setTitle("翻译结果");

    ed_tranFrom->setPlaceholderText("输入需要翻译的内容，按住 CTRL + Enter 键可以快速翻译");

    tranBtn->setCategory(MBtn_suggested);
    clearBtn->setCategory(MBtn_warning);

//    connect(tranOptionBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_FormAndTo_clicked);
    connect(pasteBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_paste_clicked);
    connect(tranBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_tran_clicked);
    connect(clearBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_clear_clicked);
    connect(copyBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_copy_clicked);
    connect(exchangeBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_exchange_clicked);
    connect(setUserInfoBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_setUserInfo_clicked);

    //链接显示翻译结果
    connect(translatetool,&TranslateTool::translateOK,this,[=](QString res){
        ed_tranTo->setText(res);
        tranToBox->setTitle("翻译结果");
    });

    //链接显示翻译结果
    connect(translatetool,&TranslateTool::disMsgAppend,this,[=](QString res){
        mNotificationBox->sendMsg(res, QIcon(":/errorIcon.png"));
        tranToBox->setTitle("翻译结果");
    });
    qDebug() << QSslSocket::supportsSsl()
             << QSslSocket::sslLibraryBuildVersionString()
             << QSslSocket::sslLibraryVersionString();
}

simplyTranslateWidget::~simplyTranslateWidget()
{

}

void simplyTranslateWidget::keyPressEvent(QKeyEvent *event)//绑定按键
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Return)
    {
        this->on_btn_tran_clicked();
    }
}

void simplyTranslateWidget::on_btn_paste_clicked() //粘贴
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    ed_tranFrom->clear();
    ed_tranFrom->setText(clipboard->text());
}

void simplyTranslateWidget::on_btn_setUserInfo_clicked() {
    if(setInfoDialog == nullptr) {
        setInfoDialog = new MDialog(this);
        setInfoDialog->addItem("百度翻译API的appId");
        setInfoDialog->addItem("百度翻译API的密钥");
    }
    auto globalSettingInstance = globalSetting::getInstance();
    if(globalSettingInstance) {
        QString appId = globalSettingInstance->readConfig("simplyTranslate", "appId");
        QString appKey = globalSettingInstance->readConfig("simplyTranslate", "appKey");
        setInfoDialog->setDefaultStrById(appId, 0);
        setInfoDialog->setDefaultStrById(appKey, 1);
    }
    else {
        mNotificationBox->sendMsg("error: 全局设置对象为null", MSG_Error);
        return;
    }
    int isSuc = setInfoDialog->exec();
    if(isSuc) {
        QString appId = setInfoDialog->getItemInfo(0);
        QString appKey = setInfoDialog->getItemInfo(1);
        globalSettingInstance->writeConfig("simplyTranslate", "appId", appId);
        globalSettingInstance->writeConfig("simplyTranslate", "appKey", appKey);
        mNotificationBox->sendMsg("设置成功", MSG_Success);
    }
    else {
        mNotificationBox->sendMsg("取消设置", MSG_Warning);
        return;
    }
}

void simplyTranslateWidget::on_btn_tran_clicked()  //翻译
{
    //获取翻译内容
    QString src = ed_tranFrom->toPlainText();
    if(src.isEmpty())
    {
        mNotificationBox->sendMsg("请输入需要翻译的内容", MSG_Warning);
        return;
    }
    QNetworkConfigurationManager mgr;
    if(!mgr.isOnline()) {
        mNotificationBox->sendMsg("网络似乎未连接...", MSG_Error);
        return;
    }
    tranToBox->setTitle("翻译中...");
    translatetool->TranslateFromBaidu(src,srcTypeMap.value(srcTypeBox->currentIndex()).second
                                      ,tarTypeMap.value(tarTypeBox->currentIndex()).second);
}

void simplyTranslateWidget::on_btn_clear_clicked() //清除
{
    ed_tranTo->clear();
    ed_tranFrom->clear();
}

void simplyTranslateWidget::on_btn_copy_clicked()  //复制
{
    if(ed_tranTo->toPlainText().isEmpty()) {
        mNotificationBox->sendMsg("翻译结果为空", MSG_Warning);
        return;
    }
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ed_tranTo->toPlainText());
    mNotificationBox->sendMsg("翻译结果成功复制到剪切板", MSG_Success);
}


void simplyTranslateWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if(isFirstShow) {
        mNotificationBox = new MNotificationBox(this);
        for(auto &pair : srcTypeMap) {
            srcTypeBox->addItem(pair.first);
        }
        for(auto &pair : tarTypeMap) {
            tarTypeBox->addItem(pair.first);
        }
        srcTypeBox->setCurrentIndex(0);
        tarTypeBox->setCurrentIndex(0);

        isFirstShow = false;
    }
}

void simplyTranslateWidget::on_btn_exchange_clicked() {
    if(srcTypeBox->currentText() == "自动检测") {
        mNotificationBox->sendMsg("目标语言不能设置为自动检测", MSG_Error);
        return;
    }
    QString &&t = srcTypeBox->currentText();
    srcTypeBox->setCurrentText(tarTypeBox->currentText());
    tarTypeBox->setCurrentText(t);
}
