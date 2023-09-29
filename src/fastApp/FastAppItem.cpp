//
// Created by mhduiy-123 on 23-8-8.
//

#include "FastAppItem.h"
#include <QPalette>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include <dfloatingbutton.h>
#include <dstyle.h>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qeasingcurve.h>
#include <qevent.h>
#include <qfont.h>
#include <qglobal.h>
#include <qguiapplication.h>
#include <qimage.h>
#include <qmargins.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qpropertyanimation.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qtextoption.h>
#include <qvariant.h>
#include <qwidget.h>

FastAppItem::FastAppItem(QWidget *parent) : 
    QWidget(parent),
    m_isHover(false),
    m_isPress(false)
{
    initUI();
    initData();
    initConnect();
}

void FastAppItem::initUI() {
    m_deleteBtn = new DFloatingButton(DStyle::StandardPixmap::SP_ForkElement, this);
    m_deleteBtn->resize(0, 0);
    m_deleteBtn->setIconSize(QSize(18,18));
    m_deleteBtn->setBackgroundRole(QPalette::Button);
    QPalette deleteBtnPalette = m_deleteBtn->palette();
    deleteBtnPalette.setColor(QPalette::Button, Qt::red);
    deleteBtnPalette.setColor(QPalette::ButtonText, Qt::white);
    m_deleteBtn->setPalette(deleteBtnPalette);

    m_editBtn = new DFloatingButton(DStyle::StandardPixmap::SP_EditElement, this);
    m_editBtn->resize(0, 0);
    m_editBtn->setIconSize(QSize(13,13));
    m_editBtn->setBackgroundRole(QPalette::Button);
    QPalette editBtnPalette = m_editBtn->palette();
    editBtnPalette.setColor(QPalette::Button, Qt::darkGreen);
    editBtnPalette.setColor(QPalette::ButtonText, Qt::white);
    m_editBtn->setPalette(editBtnPalette);

    setFixedSize(110,110);

    QTimer::singleShot(0, this, [this](){
        m_deleteBtn->move(this->width() - m_defaultBtnWidthAndHeight, 0);
        m_editBtn->move(this->width() - m_defaultBtnWidthAndHeight, m_defaultBtnWidthAndHeight + 5);

        m_deleteBtn->hide();
        m_editBtn->hide();
    });
}

void FastAppItem::initData() {
    QPoint deleteBtnLeftTop = QPoint(rect().width() - m_defaultBtnWidthAndHeight, 0);
    QPoint editBtnLeftTop = QPoint(rect().width() - m_defaultBtnWidthAndHeight, m_defaultBtnWidthAndHeight + 5);

    QPoint deleteBtnCenter = QPoint(rect().width() - m_defaultBtnWidthAndHeight / 2, m_defaultBtnWidthAndHeight / 2);
    QPoint editBtnCenter = QPoint(rect().width() - m_defaultBtnWidthAndHeight / 2, m_defaultBtnWidthAndHeight + 5 + m_defaultBtnWidthAndHeight / 2);

    m_deleteBtnOpacityAni = new QPropertyAnimation(m_deleteBtn, "windowOpacity", this);
    m_deleteBtnOpacityAni->setDuration(300);
    m_deleteBtnOpacityAni->setEasingCurve(QEasingCurve::InQuad);
    m_deleteBtnOpacityAni->setStartValue(0.0);
    m_deleteBtnOpacityAni->setEndValue(1.0);

    m_deleteBtnSizeAni = new QPropertyAnimation(m_deleteBtn, "geometry", this);
    m_deleteBtnSizeAni->setDuration(300);
    m_deleteBtnSizeAni->setEasingCurve(QEasingCurve::InQuad);
    m_deleteBtnSizeAni->setStartValue(QRect(deleteBtnCenter, QSize(0,0)));
    m_deleteBtnSizeAni->setEndValue(QRect(deleteBtnLeftTop, QSize(22,22)));

    m_editBtnOpacityAni = new QPropertyAnimation(m_editBtn, "windowOpacity", this);
    m_editBtnOpacityAni->setDuration(300);
    m_editBtnOpacityAni->setEasingCurve(QEasingCurve::InQuad);
    m_editBtnOpacityAni->setStartValue(0.0);
    m_editBtnOpacityAni->setEndValue(1.0);

    m_editBtnSizeAni = new QPropertyAnimation(m_editBtn, "geometry", this);
    m_editBtnSizeAni->setDuration(300);
    m_editBtnSizeAni->setEasingCurve(QEasingCurve::InQuad);
    m_editBtnSizeAni->setStartValue(QRect(editBtnCenter, QSize(0,0)));
    m_editBtnSizeAni->setEndValue(QRect(editBtnLeftTop, QSize(22,22)));

}

void FastAppItem::initConnect() {

}

void FastAppItem::showOperatorBtn() {
    m_editBtn->show();
    m_deleteBtn->show();
    m_deleteBtnOpacityAni->setDirection(QPropertyAnimation::Forward);
    m_deleteBtnOpacityAni->start();

    m_deleteBtnSizeAni->setDirection(QPropertyAnimation::Forward);
    m_deleteBtnSizeAni->start();

    m_editBtnOpacityAni->setDirection(QPropertyAnimation::Forward);
    m_editBtnOpacityAni->start();

    m_editBtnSizeAni->setDirection(QPropertyAnimation::Forward);
    m_editBtnSizeAni->start();
}

void FastAppItem::hideOperatorBtn() {
    m_deleteBtnOpacityAni->setDirection(QPropertyAnimation::Backward);
    m_deleteBtnOpacityAni->start();

    m_deleteBtnSizeAni->setDirection(QPropertyAnimation::Backward);
    m_deleteBtnSizeAni->start();

    m_editBtnOpacityAni->setDirection(QPropertyAnimation::Backward);
    m_editBtnOpacityAni->start();

    m_editBtnSizeAni->setDirection(QPropertyAnimation::Backward);
    m_editBtnSizeAni->start();
}

void FastAppItem::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    /* 尽可能消除锯齿边缘 */
    painter.setRenderHint(QPainter::Antialiasing);
    /* 尽可能消除文本锯齿边缘 */
    painter.setRenderHint(QPainter::TextAntialiasing);
    /* 启用线性插值算法以此来平滑图片 */
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 绘制背景

    if(m_isPress) {
        painter.setBrush(QColor::fromRgb(150, 150, 150));
        painter.setPen(Qt::darkGray);
    }
    else if(m_isHover) {
        painter.setBrush(QColor::fromRgb(190, 190, 190));
        painter.setPen(Qt::NoPen);
    }
    else {
        painter.setBrush(QColor::fromRgb(220, 220, 220));
        painter.setPen(Qt::NoPen);
    }
    painter.drawRoundedRect(rect().marginsRemoved(QMargins(5, 5, 5, 5)), 10, 10);

    // 绘制图标框

    // painter.setPen(Qt::red);
    QRect imageBorderRect = rect().marginsRemoved(QMargins(25, 25, 25, 25));
    painter.drawPixmap(imageBorderRect, QPixmap(":/bilibiliData.png"));
    // painter.drawRoundedRect(imageBorderRect, 5, 5);

    // 绘制类型

    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    QRect appTypeRect = QRect(rect().topLeft() + QPoint(8, 8), QSize(30, 15));
    painter.drawRoundedRect(appTypeRect, 5, 5);

    {
    // 绘制类型文字
        painter.setPen(Qt::black);
        QFont font;
        font.setPixelSize(10);
        painter.setFont(font);
        QTextOption titleTextOption;
        QString text = "DBUS";
        titleTextOption.setAlignment(Qt::AlignCenter);
        titleTextOption.setWrapMode(QTextOption::WrapAnywhere);
        painter.drawText(appTypeRect, text, titleTextOption);
    }



    // 绘制文字部分
    painter.setPen(Qt::black);
    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);
    QTextOption titleTextOption;
    QString text = "打开系统代理";
    QRect titleRect = rect().marginsRemoved(QMargins(5,80,5,5));
    titleTextOption.setAlignment(Qt::AlignCenter);
    titleTextOption.setWrapMode(QTextOption::WrapAnywhere);
    painter.drawText(titleRect, text, titleTextOption);

    painter.end();

    QWidget::paintEvent(event);
}

void FastAppItem::mousePressEvent(QMouseEvent *e) {
    Q_UNUSED(e)
    m_isPress = true;
    update();
}

void FastAppItem::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e)
    m_isPress = false;
    update();
}

void FastAppItem::enterEvent(QEvent *e) {
    Q_UNUSED(e)
    m_isHover = true;
    update();
}

void FastAppItem::leaveEvent(QEvent *e) {
    Q_UNUSED(e)
    m_isHover = false;
    update();
}