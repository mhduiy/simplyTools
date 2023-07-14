//
// Created by mhduiy on 2023/7/14.
//

#include "setInfoDialog.h"
#include <QLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QStandardPaths>
#include <QSettings>

SetInfoDialog::SetInfoDialog(QWidget *parent) : QWidget(parent){

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_ShowModal);

    this->setAutoFillBackground(true);
    auto *mainLayout = new QGridLayout(this);
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);    //设置窗口置顶

    sessdataEdit = new QLineEdit();
    bili_jctEdit = new QLineEdit();
    uidEdit = new QLineEdit();
    confirmBtn = new MButton("确认");
    cancelBtn = new MButton("取消");

    confirmBtn->setCategory(MBtn_suggested);

    mainLayout->addWidget(new QLabel("sessdata: "), 0, 0);
    mainLayout->addWidget(sessdataEdit, 0, 1);
    mainLayout->addWidget(new QLabel("bili_jct: "), 1, 0);
    mainLayout->addWidget(bili_jctEdit, 1, 1);
    mainLayout->addWidget(new QLabel("uid: "), 2, 0);
    mainLayout->addWidget(uidEdit, 2, 1);
    mainLayout->addWidget(confirmBtn, 3, 0);
    mainLayout->addWidget(cancelBtn, 3, 1);

    mainLayout->setSpacing(10);

    setFixedSize(300,180);
    this->setStyleSheet(" SetInfoDialog { border: 1px lightblue solid; border-radius: 10px;} ");

    connect(confirmBtn, &QPushButton::clicked, this, &SetInfoDialog::setIniInfo);
    connect(cancelBtn, &QPushButton::clicked, this, [this](){
        this->close();
        emit exitDialog(true);
    });

    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    settings = new QSettings(cacheDir + "/config.ini", QSettings::IniFormat);

    sessdataEdit->setText(settings->value("bilibiliData/sessdata").toString());
    bili_jctEdit->setText(settings->value("bilibiliData/bili_jct").toString());
    uidEdit->setText(settings->value("bilibiliData/uid").toString());
}

void SetInfoDialog::setIniInfo() {
    QString sessdata = sessdataEdit->text();
    QString bili_jct = bili_jctEdit->text();
    QString uid = uidEdit->text();

    // 写入字符串值
    settings->setValue("bilibiliData/sessdata", sessdata);

    // 写入整数值
    settings->setValue("bilibiliData/bili_jct", bili_jct);

    // 写入浮点数值
    settings->setValue("bilibiliData/uid", uid);

    emit exitDialog(false);
    this->close();
}
