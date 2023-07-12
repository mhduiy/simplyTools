//
// Created by mhduiy on 2023/7/13.
//

#include "MNotificationBox.h"
#include <QDebug>
#include <QLayout>
#include <QFile>

MNotificationWidget::MNotificationWidget(QWidget *mainWindow) : QWidget(mainWindow){
    setFixedSize(300,60);

    contentLabel = new QLabel;
    iconLabel = new QLabel;
    closeBtn = new MButton("");
    closeBtn->setIcon(QIcon(":/closeIcon.png"));

    auto *mainLayout = new QHBoxLayout(this);

    iconLabel->setFixedSize(30,30);
    closeBtn->setFixedSize(30,30);

    iconLabel->setScaledContents(true);

    QFont font;
    font.setFamily("黑体");
    font.setPixelSize(16);
    contentLabel->setFont(font);
    contentLabel->setAlignment(Qt::AlignCenter);

//    contentLayout->addWidget(iconLabel);
//    contentLayout->addWidget(contentLabel);
//    contentLayout->setSpacing(10);

    mainLayout->addWidget(iconLabel, 1);
    mainLayout->addWidget(contentLabel ,4);
    mainLayout->addWidget(closeBtn, 1);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setAutoFillBackground(true);
    this->setStyleSheet("MNotificationWidget{\n"
                        "    background-color: #ffffff;\n"
                        "    border: 1px lightblue solid;\n"
                        "    border-radius: 12px;\n"
                        "}");

//    closeBtn->setVisible(false);

    connect(closeBtn, &QPushButton::clicked, this, &MNotificationWidget::closeBtnClicked);
}

MNotificationWidget::~MNotificationWidget() {
    if(contentLabel != nullptr) {
        contentLabel->deleteLater();
    }
    if(iconLabel != nullptr) {
        iconLabel->deleteLater();
    }
    if(closeBtn != nullptr) {
        closeBtn->deleteLater();
    }
}

void MNotificationWidget::setContent(const QString &content, const QIcon &icon) {
    contentLabel->setText(content);
    iconLabel->setPixmap(icon.pixmap(30,30));
}

MNotificationBox::MNotificationBox(QWidget *cutWidget){

    m_animation = new QPropertyAnimation();
    mainWindow = findMainWindow(cutWidget);
    this->setParent(mainWindow);
    msgWidget = new MNotificationWidget(mainWindow);

    m_animation->setTargetObject(msgWidget);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    m_animation->setDuration(600);
    m_animation->setPropertyName("pos");
    msgWidget->setVisible(false);
    msgWidget->raise();

    connect(&timer, &QTimer::timeout, this, &MNotificationBox::closeMsgWidget);
    connect(msgWidget, &MNotificationWidget::closeBtnClicked, this, &MNotificationBox::closeMsgWidget);
}

void MNotificationBox::sendMsg(const QString &content, const QIcon &icon, int duration) {
    msgWidget->setContent(content, icon);
    this->duration = duration;
    openMsgWidget();
}

void MNotificationBox::closeMsgWidget() {
    cutPoint = msgWidget->pos();
    tarPoint = QPoint((mainWindow->width() - msgWidget->width()) / 2, -1 * msgWidget->height());
    m_animation->setStartValue(cutPoint);
    m_animation->setEndValue(tarPoint);
    m_animation->start();
    timer.stop();
}

void MNotificationBox::openMsgWidget() {
    msgWidget->move(QPoint((mainWindow->width() - msgWidget->width()) / 2, -1 * msgWidget->height()));

    cutPoint = msgWidget->pos();
    tarPoint = cutPoint;
    tarPoint.setX((mainWindow->width() - msgWidget->width()) / 2);
    tarPoint.setY(20);

    msgWidget->setVisible(true);;

    m_animation->setStartValue(cutPoint);
    m_animation->setEndValue(tarPoint);
    m_animation->start();
    timer.start(duration * 1000);
}

QWidget *MNotificationBox::findMainWindow(QObject *obj) {
    if(obj == nullptr) {
        return nullptr;
    }
    qDebug() << obj->metaObject()->className();
    if(strcmp(obj->metaObject()->className(), "MainWindow") == 0) {
        return qobject_cast<QWidget*>(obj);
    }
    return findMainWindow(obj->parent());
}