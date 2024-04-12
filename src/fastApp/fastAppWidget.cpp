//
// Created by mhduiy-123 on 23-8-8.
//

#include "fastAppWidget.h"
#include <QLayout>
#include <QPushButton>
#include "FastAppItem.h"
#include "customComponents/MTabSwitchButton.h"
#include "fastApp/FastAppWoker.h"
#include <QDebug>

FastAppWidget::FastAppWidget(QWidget *parent)
:QWidget(parent)
,m_editFastAppBtn(new QPushButton())
,m_addFastAppBtn(new QPushButton())
,m_worker(new FastAppWorker(this))
{
    auto *mainLayout = new QVBoxLayout(this);
    m_mainWidget = new FlowLayoutWidget(this);
    for(int i = 0; i < 100; i++) {
        m_fastAppItems.append(new FastAppItem);
    }


    for(auto item : m_fastAppItems) {
        m_mainWidget->addItem(item);
    }

    /*******test*******/
    auto tabSwitchBtn = new MTabSwitchButton();

    tabSwitchBtn->addItem("启动App");
    tabSwitchBtn->addItem("执行命令");
    tabSwitchBtn->addItem("运行DBUS");
    tabSwitchBtn->addItem("测试1");
    tabSwitchBtn->addItem("测试2");
    QHBoxLayout *ll = new QHBoxLayout();
    ll->addWidget(tabSwitchBtn);
    ll->setAlignment(Qt::AlignHCenter);

    mainLayout->addLayout(ll);

    connect(tabSwitchBtn, QOverload<int, int>::of(&MTabSwitchButton::currentIndexChanged), this, [](int preIndex, int curIndex){
        qWarning() << "切换tab" << preIndex << "->" << curIndex;
    });
    /*******test*******/

    mainLayout->addWidget(m_mainWidget);

    m_editFastAppBtn->raise();
    m_addFastAppBtn->raise();
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
        isShow = false;
    }
    else {
        for(auto item : m_fastAppItems) {
            item->showOperatorBtn();
        }
        isShow = true;
    }
}

void FastAppWidget::onAddFastAppBtnClicked()
{
    m_worker->showDialog();
}