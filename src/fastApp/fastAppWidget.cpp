//
// Created by mhduiy-123 on 23-8-8.
//

#include "fastAppWidget.h"
#include <QLayout>
#include <dsuggestbutton.h>
#include <qpushbutton.h>
#include "FastAppItem.h"

FastAppWidget::FastAppWidget(QWidget *parent)
:QWidget(parent)
,m_editFastAppBtn(new DFloatingButton(DStyle::SP_EditElement, this))
,m_addFastAppBtn(new DFloatingButton(DStyle::SP_IncreaseElement, this))
{
    auto *mainLayout = new QVBoxLayout(this);
    m_mainWidget = new FlowLayoutWidget(this);
    for(int i = 0; i < 100; i++) {
        m_fastAppItems.append(new FastAppItem);
    }


    for(auto item : m_fastAppItems) {
        m_mainWidget->addItem(item);
    }

    mainLayout->addWidget(m_mainWidget);

    // mainLayout->addLayout(main1);
    // mainLayout->addLayout(main2);
    // mainLayout->addLayout(main3);
    // mainLayout->addWidget(m_editFastAppBtn);
    // mainLayout->addWidget(m_addFastAppBtn);

    m_editFastAppBtn->raise();
    m_addFastAppBtn->raise();

    connect(m_editFastAppBtn, &DFloatingButton::clicked, this, &FastAppWidget::onEditFastAppBtnClicked);
    connect(m_addFastAppBtn, &DFloatingButton::clicked, this, &FastAppWidget::onAddFastAppBtnClicked);

}


void FastAppWidget::resizeEvent(QResizeEvent *event)
{
    m_editFastAppBtn->move(this->geometry().width() - m_editFastAppBtn->width() - 10, this->geometry().height() - m_editFastAppBtn->height() - 10);
    m_addFastAppBtn->move(this->geometry().width() - m_editFastAppBtn->width() * 2 - 20, this->geometry().height() - m_editFastAppBtn->height() - 10);
    QWidget::resizeEvent(event);
}

void FastAppWidget::showEvent(QShowEvent *event)
{
    static bool isFirstShow = true;
    QWidget::showEvent(event);
    if(!isFirstShow) {
        return;
    }
    isFirstShow = false;
    m_editFastAppBtn->move(this->geometry().width() - m_editFastAppBtn->width() - 10, this->geometry().height() - m_editFastAppBtn->height() - 10);
    m_addFastAppBtn->move(this->geometry().width() - m_editFastAppBtn->width() * 2 - 20, this->geometry().height() - m_editFastAppBtn->height() - 10);
}

void FastAppWidget::onEditFastAppBtnClicked()
{
    static bool isShow = false;
    if(isShow) {
        for(auto item : m_fastAppItems) {
            item->hideOperatorBtn();
        }
        m_editFastAppBtn->setIcon(DStyle::StandardPixmap::SP_EditElement);
        isShow = false;
    }
    else {
        for(auto item : m_fastAppItems) {
            item->showOperatorBtn();
        }
        m_editFastAppBtn->setIcon(DStyle::StandardPixmap::SP_MarkElement);
        isShow = true;
    }
}

void FastAppWidget::onAddFastAppBtnClicked()
{

}