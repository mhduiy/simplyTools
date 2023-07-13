//
// Created by mhduiy on 2023/7/13.
//

#include "bilibiliDataWidget.h"
#include <QLayout>
#include <QPixmap>

BilibiliDataWidget::BilibiliDataWidget(QWidget *parent)  : QWidget(parent){
    initUI();
    initData();
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

    headLayout->addWidget(headImageLabel, 3);
    headLayout->addLayout(userInfoLayout, 3);
    headLayout->addStretch(1);
    headLayout->addLayout(operatorBtnLayout, 3);

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
}


void BilibiliDataWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if(mNotificationBox == nullptr) {
        mNotificationBox = new MNotificationBox(this);
    }

}

void BilibiliDataWidget::updateBtnClicked() {
    mNotificationBox->sendMsg("功能还在建设中...", MSG_Success);
}

void BilibiliDataWidget::setInfoBtnClicked() {
    mNotificationBox->sendMsg("功能还在建设中...", MSG_Success);
}