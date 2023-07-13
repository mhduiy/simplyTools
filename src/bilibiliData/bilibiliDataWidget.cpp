//
// Created by mhduiy on 2023/7/13.
//

#include "bilibiliDataWidget.h"
#include <QLayout>
#include <QPixmap>
#include <QDebug>

BilibiliDataWidget::BilibiliDataWidget(QWidget *parent)  : QWidget(parent){
    initUI();
}

void BilibiliDataWidget::initUI() {
    headImageLabel = new QLabel();
    headImageLabel->setScaledContents(true);
    headImageLabel->setPixmap(QPixmap(":/successIcon.png"));
    headImageLabel->setFixedSize(100, 100);
    headImageLabel->setMargin(5);

    headImageLabel->setStyleSheet("QLabel{ border: 1px solid lightgray; border-radius: 50px;}");

    userNameLabel = new QLabel("用户名: ******");
    uidLabel = new QLabel("UID: ******");
    levelLabel = new QLabel("等级: LV.5");

    userNameLabel->setStyleSheet("font-family: 黑体;  border-radius: 5px; background-color: #FFB5B5; padding: 2px 2px 4px 1px;");
    uidLabel->setStyleSheet("font-family: 黑体;  border-radius: 5px; background-color: #D5B4FF; padding: 2px 2px 4px 1px;");
    levelLabel->setStyleSheet("font-family: 黑体;  border-radius: 5px; background-color: #B8CDFF; padding: 2px 2px 4px 1px;");

    setInfoBtn = new MButton("设置信息");
    updateBtn = new MButton("刷新一下");
    setInfoBtn->setCategory(MBtn_suggested);
    updateBtn->setCategory(MBtn_suggested);

    coinCountLabel = new MIcon("我的硬币", "*****");
    followCountLabel = new MIcon("我的关注", "*****");
    fanCountLabel = new MIcon("我的粉丝", "*****");
    likeCountLabel = new MIcon("获得点赞", "*****");
    playCountLabel = new MIcon("获得播放", "*****");
    readCountLabel = new MIcon("获得阅读", "*****");


    auto *mainLayout = new QVBoxLayout(this);
    auto *headLayout = new QHBoxLayout();
    auto *userInfoLayout = new QVBoxLayout();
    auto *operatorBtnLayout = new QVBoxLayout();
    auto *displayLayout = new QGridLayout();

    mainLayout->setAlignment(Qt::AlignJustify);

    userInfoLayout->addWidget(userNameLabel);
    userInfoLayout->addWidget(uidLabel);
    userInfoLayout->addWidget(levelLabel);

    userInfoLayout->setMargin(10);

    operatorBtnLayout->addWidget(setInfoBtn);
    operatorBtnLayout->addWidget(updateBtn);

    headLayout->addWidget(headImageLabel, 5);
    headLayout->addLayout(userInfoLayout, 5);
    headLayout->addStretch(1);
    headLayout->addLayout(operatorBtnLayout, 5);

    displayLayout->addWidget(coinCountLabel, 0, 0);
    displayLayout->addWidget(followCountLabel, 0, 1);
    displayLayout->addWidget(fanCountLabel, 0, 2);
    displayLayout->addWidget(likeCountLabel, 1, 0);
    displayLayout->addWidget(playCountLabel, 1, 1);
    displayLayout->addWidget(readCountLabel, 1, 2);

    mainLayout->addLayout(headLayout, 2);
    mainLayout->addStretch(1);
    mainLayout->addLayout(displayLayout, 2);
    mainLayout->setMargin(20);
    displayLayout->setSpacing(20);
}

void BilibiliDataWidget::initData() {
    connect(setInfoBtn, &MButton::clicked, this, &BilibiliDataWidget::setInfoBtnClicked);
    connect(updateBtn, &MButton::clicked, this, &BilibiliDataWidget::updateBtnClicked);
    connect(updateBtn, &MButton::clicked, biliBiliDataTool, &BiliBiliDataTool::getData);
    connect(biliBiliDataTool, &BiliBiliDataTool::readUserImageFinish, [this](const QPixmap& pixmap){
        headImageLabel->setPixmap(pixmap);
    });
}


void BilibiliDataWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if(mNotificationBox == nullptr) {
        mNotificationBox = new MNotificationBox(this);
    }
    if(biliBiliDataTool == nullptr) {
        biliBiliDataTool = new BiliBiliDataTool();
        connect(biliBiliDataTool, &BiliBiliDataTool::readFinish, this, &BilibiliDataWidget::showData);
        connect(biliBiliDataTool, &BiliBiliDataTool::readError, this, [this](const QString& str){
            this->mNotificationBox->sendMsg("读取失败: " + str, MSG_Error);
        });
    }
    if(getBiliBiliDataThread == nullptr) {
        getBiliBiliDataThread = new QThread();
        biliBiliDataTool->moveToThread(getBiliBiliDataThread);
        getBiliBiliDataThread->start();
    }

    if(isFirstShow) {
        initData();
        isFirstShow = false;
    }
}

void BilibiliDataWidget::updateBtnClicked() {
    mNotificationBox->sendMsg("正在获取数据", MSG_Warning);
//    biliBiliDataTool->getData();
}

void BilibiliDataWidget::setInfoBtnClicked() {
    mNotificationBox->sendMsg("功能还在建设中...", MSG_Success);
}

void BilibiliDataWidget::showData(const QMap<int, QString>& info) {
    userNameLabel->setText("用户名: " + info.value(BL_userName, "*读取失败*"));
    uidLabel->setText("UID: " + info.value(BL_uid, "*读取失败*"));
    levelLabel->setText("等级: LV." + info.value(BL_level, "*读取失败*"));

    coinCountLabel->setText(info.value(BL_coinCount, "*读取失败*"));
    followCountLabel->setText(info.value(BL_followCount, "*读取失败*"));
    fanCountLabel->setText(info.value(BL_fansCount, "*读取失败*"));
    likeCountLabel->setText(info.value(BL_likeCount, "*读取失败*"));
    playCountLabel->setText(info.value(BL_playCount, "*读取失败*"));
    readCountLabel->setText(info.value(BL_readCount, "*读取失败*"));

    mNotificationBox->sendMsg("刷新成功", MSG_Warning);

    biliBiliDataTool->getImageFromUrl(info.value(BL_iconUrl));
}
