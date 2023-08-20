//
// Created by mhduiy-123 on 23-8-8.
//

#ifndef SIMPLYTOOLS_FASTAPPWIDGET_H
#define SIMPLYTOOLS_FASTAPPWIDGET_H

#include "fastApp/FastAppItem.h"
#include <QWidget>
#include <QVector>
#include <DSuggestButton>
#include <dsuggestbutton.h>

class FastAppWidget : public QWidget{
    Q_OBJECT
public:
    explicit FastAppWidget(QWidget *parent = nullptr);

private:
    QVector<FastAppItem*> m_fastAppItems;
    DSuggestButton *editBtn;
};


#endif //SIMPLYTOOLS_FASTAPPWIDGET_H
