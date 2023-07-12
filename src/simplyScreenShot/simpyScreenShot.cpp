//
// Created by mhduiy on 2023/7/12.
//

#include "simpyScreenShot.h"
#include <QLayout>
#include <QGroupBox>
#include <QFile>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QThread>

SimpyScreenShot::SimpyScreenShot(QWidget *parent) : QWidget(parent){
    initUI();
}
// 取色器： 按钮   颜色快：值
void SimpyScreenShot::initUI() {
    auto *mainLayout = new QVBoxLayout(this);

    imageDisPlay = new QLabel();
    copyImageBtn = new MButton("复制到剪切板");
    saveImageBtn = new MButton("保存");
    startColorPicker = new MButton("屏幕取色");
    startScreenShotBtn = new MButton("屏幕截图");
    colorDis = new QLabel();
    colorValue = new QLineEdit();
    copyColorValueBtn = new MButton("复制颜色");

    startColorPicker->setCategory(MBtn_suggested);
    startScreenShotBtn->setCategory(MBtn_suggested);
    startColorPicker->setFixedWidth(150);
    startScreenShotBtn->setFixedWidth(150);

    colorDis->setStyleSheet("QLabel { border: 1px solid rgb(64,158,255); padding: 3px; }");
    colorDis->setFixedSize(36,36);

    auto *operatorLayout = new QGridLayout();

    operatorLayout->addWidget(startScreenShotBtn, 0, 0);
    operatorLayout->addWidget(saveImageBtn, 0, 1,1,2);
    operatorLayout->addWidget(copyImageBtn, 0, 3);
    operatorLayout->addWidget(startColorPicker, 1, 0);
    operatorLayout->addWidget(colorDis, 1, 1);
    operatorLayout->addWidget(colorValue, 1, 2);
    operatorLayout->addWidget(copyColorValueBtn, 1, 3);

    auto *imageBox = new QGroupBox();
    imageBox->setLayout(new QHBoxLayout);
    imageBox->layout()->addWidget(imageDisPlay);

    mainLayout->addWidget(imageBox);
    mainLayout->addLayout(operatorLayout);

    QFile file(":/screen.qss");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        QString &&str = file.readAll();
        this->setStyleSheet(str);
        file.close();
    }

    connect(startScreenShotBtn, &MButton::clicked, this, &SimpyScreenShot::screenShotOperator);
    connect(startColorPicker, &MButton::clicked, this, &SimpyScreenShot::colorPickerOperator);
    connect(copyImageBtn, &MButton::clicked, this, &SimpyScreenShot::copyImageOperator);
    connect(saveImageBtn, &MButton::clicked, this, &SimpyScreenShot::saveImageOperator);
    connect(copyColorValueBtn, &MButton::clicked, this, &SimpyScreenShot::copyColorOperator);
}

void SimpyScreenShot::screenShotOperator() {
    QObject *obj = this->parent()->parent()->parent();
    if(QString(obj->metaObject()->className()) == "MainWindow") {
        qobject_cast<QWidget*>(obj)->hide();
    }
    QScreen *screen = QGuiApplication::primaryScreen();
    pixmap = screen->grabWindow(0);
    imageDisPlay->setScaledContents(true);   // 设置图片自动缩放
    imageDisPlay->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);  // 设置大小策略
    imageDisPlay->setPixmap(pixmap);
    if(QString(obj->metaObject()->className()) == "MainWindow") {
        qobject_cast<QWidget*>(obj)->show();
    }
}

void SimpyScreenShot::colorPickerOperator() {

}

void SimpyScreenShot::copyImageOperator() {

}

void SimpyScreenShot::saveImageOperator() {

}

void SimpyScreenShot::copyColorOperator() {

}
