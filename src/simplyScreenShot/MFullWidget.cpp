//
// Created by mhduiy on 2023/7/12.
//

#include "MFullWidget.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

MFullWidget::MFullWidget(QWidget *parent) : QWidget(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void MFullWidget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        emit leftMousePressed();
    }
    if(event->button() == Qt::RightButton) {
        emit rightMousePressed();
    }
    QWidget::mousePressEvent(event);
}

void MFullWidget::keyPressEvent(QKeyEvent *event) {
    // bug
    if(event->key() == Qt::Key_Escape) {
        emit escKeyPressed();
    }
    QWidget::keyPressEvent(event);
}
