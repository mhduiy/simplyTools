//
// Created by mhduiy-123 on 23-8-8.
//

#include "fastAppWidget.h"
#include <QLayout>
#include "customComponents/FastAppItem.h"

FastAppWidget::FastAppWidget(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(new FastAppItem);
    mainLayout->addWidget(new FastAppItem);
    mainLayout->addWidget(new FastAppItem);
    mainLayout->addWidget(new FastAppItem);
}
