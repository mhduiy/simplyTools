//
// Created by mhduiy on 2023/7/11.
//

#include "MButton.h"
#include <QFile>
#include <QVariant>
#include <QDebug>
#include <QStyle>

MButton::MButton(const QString &text, QWidget *parent) : QPushButton(text, parent){
    // 加载样式表
    QFile file(":/MButton.qss");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        setStyleSheet(file.readAll());
    }
    file.close();

    setCategory(MBtn_ordinary); //设置默认按钮样式
}

void MButton::setCategory(Category category)
{
    qDebug() << category;
    this->category = category;
    setProperty("style", QVariant(category));

    //重新加载一遍样式
    this->style()->unpolish(this);
    this->style()->polish(this);
}
