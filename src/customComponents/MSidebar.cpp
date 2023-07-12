//
// Created by mhduiy on 2023/7/11.
//

#include "MSidebar.h"
#include <QLayout>
#include <QFile>
#include <QPoint>
#include <QDebug>

const int DEFAULTWIDTH = 180;

MSidebar::MSidebar(QWidget *parent) : QWidget(parent) {
    initUI();
}

void MSidebar::initUI() {
    setAttribute(Qt::WA_StyledBackground);
    auto *mainLayout = new QHBoxLayout(this);

    listWidget = new QListWidget();
    foldBtn = new QPushButton(this);
    foldBtn->setIcon(QIcon(":/left-arrow.png"));
    foldBtn->setFixedSize(20, 20);
    foldBtn->setIconSize(QSize(20, 20));
    foldBtn->setStyleSheet("QPushButton{border: 0px; border-radius: 20px; margin: 0px; padding: 0px}  QPushButton:hover{background-color: #ececec;}");

    setContentsMargins(0,0,0,0);

    mainLayout->setSpacing(0);
    mainLayout->addWidget(listWidget);
//    mainLayout->addWidget(foldBtn);
    setFixedWidth(180);

    // 加载样式表
    QFile file(":/sidebar.qss");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        this->setStyleSheet(file.readAll());
    }
    file.close();
    foldBtn->raise();   //置于顶层
    this->layout()->setMargin(5);

    connect(&animationTimer, &QTimer::timeout, this, &MSidebar::moveWidget);
//    connect(foldBtn, &QPushButton::clicked, this, &MSidebar::foldPage);
}

void MSidebar::addWidgetItem(const QString &text, const QIcon& icon) {
    auto *item = new QListWidgetItem(icon, text);
//    item->setSizeHint(QSize(20, 60));
    this->listWidget->addItem(item);
}

void MSidebar::foldPage() {
    cutX = this->pos().x();
    if(cutX == -1 * this->width() + foldBtn->width()) { //当前是折叠状态
        tarX = 0;  //设置为展开
    }
    else if(cutX == 0){ // 当前是展开状态
        tarX = -1 * this->width() + foldBtn->width();
    }
    else {
        return;
    }
    animationTimer.start(1);
}

void MSidebar::moveWidget() {
    if(tarX == cutX) {
        animationTimer.stop();
        QIcon icon = foldBtn->icon();
        QPixmap pixmap = icon.pixmap(64, 64);
        QTransform transform;
        transform.rotate(180);
        pixmap = pixmap.transformed(transform);
        foldBtn->setIcon(pixmap);
    }
    else if(cutX < tarX){
        cutX += 1;
    }
    else {
        cutX -= 1;
    }
    this->move(cutX, this->pos().y());
}

void MSidebar::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if(isFirstShow) {
        foldBtn->move(this->pos().x() + this->width() - foldBtn->width(), (this->pos().y() + this->height() - foldBtn->height()) / 2 );
        setCurrentIndex(0); //设置默认选择项
        connect(listWidget, &QListWidget::currentRowChanged, this, &MSidebar::currentIndexChanged);
        foldPage();
        isFirstShow = false;
    }
}

void MSidebar::setCurrentIndex(int index) {
    listWidget->setCurrentIndex(listWidget->model()->index(index, 0));
}

void MSidebar::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    foldBtn->move(this->pos().x() + this->width() - foldBtn->width(), (this->pos().y() + this->height() - foldBtn->height()) / 2 );
}

void MSidebar::enterEvent(QEvent *event) {
    foldPage();
}

void MSidebar::leaveEvent(QEvent *event) {
    foldPage();
}
