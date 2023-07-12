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

    m_animation = new QPropertyAnimation();
    m_animation->setTargetObject(this);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    m_animation->setDuration(800);
    m_animation->setPropertyName("pos");
}

void MSidebar::addWidgetItem(const QString &text, const QIcon& icon) {
    auto *item = new QListWidgetItem(icon, text);
//    item->setSizeHint(QSize(20, 60));
    this->listWidget->addItem(item);
}

void MSidebar::foldPage() {
    cutPos = this->pos();
    tarPos = cutPos;
    if(cutPos.x() == -1 * this->width() + foldBtn->width()) { //当前是折叠状态
        tarPos.setX(0);  //设置为展开
    }
    else if(cutPos.x() == 0){ // 当前是展开状态
        tarPos.setX(-1 * this->width() + foldBtn->width());
    }
    else {  // 当前在动画中
        return;
    }
    m_animation->setStartValue(cutPos);
    m_animation->setEndValue(tarPos);
    m_animation->start();   //开始动画
    // 翻转图标
    QIcon icon = foldBtn->icon();
    QPixmap pixmap = icon.pixmap(64, 64);
    QTransform transform;
    transform.rotate(180);
    pixmap = pixmap.transformed(transform);
    foldBtn->setIcon(pixmap);
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
