//
// Created by mhduiy-123 on 23-8-8.
//

#include "FastAppItem.h"
#include <QPalette>
#include <QLabel>
#include <QLayout>
#include <QTimer>

FastAppItem::FastAppItem(QWidget *parent) : QWidget(parent){
    initUI();
}

void FastAppItem::initUI() {
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::yellow);
    setPalette(palette);

    dFloatingButton = new DFloatingButton(DStyle::StandardPixmap::SP_ForkElement, this);
    dFloatingButton->setFixedSize(20,20);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Test"));
//    mainLayout->addWidget(dFloatingButton);

    setFixedSize(100,100);

    QTimer::singleShot(0, this, [this](){
        dFloatingButton->move(this->width() - dFloatingButton->width(), 0);
    });
}
