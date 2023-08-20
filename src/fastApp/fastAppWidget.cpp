//
// Created by mhduiy-123 on 23-8-8.
//

#include "fastAppWidget.h"
#include <QLayout>
#include <dsuggestbutton.h>
#include <qpushbutton.h>
#include "FastAppItem.h"

FastAppWidget::FastAppWidget(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QHBoxLayout(this);
    m_fastAppItems.append(new FastAppItem);
    m_fastAppItems.append(new FastAppItem);
    m_fastAppItems.append(new FastAppItem);
    m_fastAppItems.append(new FastAppItem);
    for(auto item : m_fastAppItems) {
        mainLayout->addWidget(item);
    }
    editBtn = new DSuggestButton();
    mainLayout->addWidget(editBtn);

    connect(editBtn, &QPushButton::clicked, this, [this](){
        static bool isShow = false;
        if(isShow) {
            for(auto item : m_fastAppItems) {
                item->hideOperatorBtn();
            }
            isShow = false;
        }
        else {
                for(auto item : m_fastAppItems) {
                item->showOperatorBtn();
            }
            isShow = true;
        }

    });
}
