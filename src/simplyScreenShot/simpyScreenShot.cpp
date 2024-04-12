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
#include <QMessageBox>
#include <QColor>
#include <QRgb>
#include <QFileDialog>
#include <QDateTime>
#include <QBuffer>
#include <QDir>
#include <QClipboard>
#include <qlabel.h>

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
    connect(&timer, &QTimer::timeout, this, &SimpyScreenShot::showColorPicker);
}

void SimpyScreenShot::screenShotOperator() {
    mainWindow->hide();
    QThread::msleep(100);
    QScreen *screen = QGuiApplication::primaryScreen();
    pixmap = screen->grabWindow(0);
    imageDisPlay->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);  // 设置大小策略
    imageDisPlay->setPixmap(pixmap);
    mainWindow->show();
}

// 先是一个框（透明的）等待用户开始剪切，

void SimpyScreenShot::colorPickerOperator() {
    if(mainWindow) {
        mainWindow->hide();
        QThread::msleep(100);
    }
    // 截一个图， 全屏显示
    QScreen *screen = QGuiApplication::primaryScreen();
    tmpPixmap = screen->grabWindow(0);

    // 截图后显示以无边框窗口全屏显示
    if(showImageWidget == nullptr) {
        showImageWidget = new MFullWidget();

        showImageWidget->setLayout(new QHBoxLayout);
        showScreenImageLabel = new QLabel();
        showImageWidget->layout()->addWidget(showScreenImageLabel);
        showImageWidget->layout()->setMargin(0);

        connect(showImageWidget, &MFullWidget::leftMousePressed, this, &SimpyScreenShot::exitColorWidget);
        connect(showImageWidget, &MFullWidget::rightMousePressed, this, &SimpyScreenShot::exitColorWidget);
        connect(showImageWidget, &MFullWidget::escKeyPressed, this, &SimpyScreenShot::exitColorWidget);

    }

    // 显示颜色的小窗口
    if(showColorBox == nullptr) {
        showColorBox = new QWidget();
        showColorBox->setWindowFlag(Qt::FramelessWindowHint);
        showColorBox->setLayout(new QVBoxLayout);
        colorLabelInDialog = new QLabel("颜色:");
        posLabelInDialog = new QLabel("位置:");
        colorDisInDialog = new QLabel();
        colorDisInDialog->setAutoFillBackground(true);

        colorDisInDialog->setFixedSize(150,80);
        auto palette = colorDisInDialog->palette();
        palette.setColor(QPalette::Background, Qt::red);
        colorDisInDialog->setPalette(palette);

        showColorBox->layout()->addWidget(colorDisInDialog);
        showColorBox->layout()->addWidget(posLabelInDialog);
        showColorBox->layout()->addWidget(colorLabelInDialog);

        showColorBox->layout()->setMargin(0);
        showColorBox->setFixedSize(150,150);
    }
    showScreenImageLabel->setPixmap(tmpPixmap);
    showImageWidget->showMaximized();
    showColorBox->show();
    timer.start(3);
    QGuiApplication::setOverrideCursor(Qt::CrossCursor);    //修改鼠标样式
}

void SimpyScreenShot::copyImageOperator() {
    if (pixmap.isNull()) {
        mNotificationBox->sendMsg("没截图不能复制 (●'◡'●)", MSG_Warning);
        return;
    }
        QClipboard *clipboard = QGuiApplication::clipboard(); // 获取剪贴板对象
        clipboard->setPixmap(pixmap); // 将图片复制到剪贴板
    mNotificationBox->sendMsg("图片已复制到剪切板", MSG_Success);
}

void SimpyScreenShot::saveImageOperator() {
    if(pixmap.isNull()) {
        mNotificationBox->sendMsg("没截图不能保存 (●'◡'●)", MSG_Warning);
        return;
    }
    QString &&saveDir = QFileDialog::getExistingDirectory(this, "选择保存路径");
    QString &&fileName = QDateTime::currentDateTime().toString("MMddhhmm");
    QString filePath = saveDir + "/" + fileName + ".png";

    if(saveDir.isEmpty()) {
        return;
    }

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");

    QFile file(filePath);
    qDebug() << file.fileName();
    file.open(QIODevice::WriteOnly);
    bool ret = false;
    if(file.isOpen()) {
        ret = file.write(bytes);
        file.flush();
        file.close();
    }

    if(ret != 0) {
        mNotificationBox->sendMsg("保存成功", MSG_Success);
    }
    else {
        mNotificationBox->sendMsg("保存失败", MSG_Error);
    }
}

void SimpyScreenShot::copyColorOperator() {
    if(strHex.isEmpty()) {
        mNotificationBox->sendMsg("还没有取色哦 (*>﹏<*)", MSG_Warning);
        return;
    }
    QClipboard *clipboard = QGuiApplication::clipboard(); // 获取剪贴板对象
    clipboard->setText(strHex);
    mNotificationBox->sendMsg("已复制到剪切板", MSG_Success);
}

void SimpyScreenShot::showColorPicker() {
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();

    int tarX = x + 5;
    int tarY = y - showColorBox->height() - 5;

    if(y - showColorBox->height() < 0) {    //超出上边界
        tarY = y + 5;
    }
    if(x + showColorBox->width() > QGuiApplication::primaryScreen()->geometry().width()) { //超出右边界
        tarX = x - showColorBox->width() - 5;
    }
    showColorBox->move(tarX, tarY);

    posLabelInDialog->setText(QString("位置:(%1, %2)").arg(x).arg(y));

    QScreen *screen = qApp->primaryScreen();
    auto pixmapTmp = tmpPixmap.copy(x,y,2,2);

    if (pixmapTmp.isNull()) {
        return;
    }
    QImage image = pixmapTmp.toImage();
    if (image.valid(0, 0)) {
        cutColor = image.pixel(0, 0);
        auto p = colorDisInDialog->palette();
        p.setColor(QPalette::Background, cutColor);
        colorDisInDialog->setPalette(p);
        strDecimalValue = QString("rgb(%1,%2,%3)").arg(qRed(cutColor.rgb())).arg(qGreen(cutColor.rgb())).arg(qBlue(cutColor.rgb()));
        strHex = "#" + QString::number(cutColor.rgb(), 16).right(6).toUpper();
    }

    colorLabelInDialog->setText(QString("%1\nhex(%2)").arg(strDecimalValue, strHex));
}

void SimpyScreenShot::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
}

void SimpyScreenShot::exitColorWidget() {
    if(showImageWidget != nullptr) {
        showImageWidget->hide();
        showImageWidget->deleteLater();
        showImageWidget = nullptr;
    }
    if(showColorBox != nullptr) {
        showColorBox->hide();
        showColorBox->deleteLater();
        showColorBox = nullptr;
    }
    this->show();
    if(timer.isActive()) {}
    timer.stop();
    if(mainWindow) {
        mainWindow->show();
    }
    colorValue->setText(strHex + " " + strDecimalValue);

    auto p = colorDis->palette();
    colorDis->setAutoFillBackground(true);
    p.setColor(QPalette::Background, cutColor);
    colorDis->setPalette(p);
    QGuiApplication::restoreOverrideCursor();  // 恢复鼠标样式
}

void SimpyScreenShot::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    // 获取MainWindow对象， 实现隐藏显示
    if(mainWindow == nullptr) {
        QObject *obj = this->parent()->parent()->parent();
        if(strcmp(obj->metaObject()->className(), "MainWindow") == 0) {
            mainWindow = qobject_cast<QWidget*>(obj);
        }
    }
    if(mNotificationBox == nullptr) {
        mNotificationBox = new MNotificationBox(this);
    }
}