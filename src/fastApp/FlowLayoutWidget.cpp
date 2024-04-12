#include "FlowLayoutWidget.h"
#include <QResizeEvent>
#include <QDebug>
#include <qboxlayout.h>

FlowLayoutWidget::FlowLayoutWidget(QWidget *parent)
:QScrollArea(parent)
,m_contentLayout(new QVBoxLayout())
,m_contentWidget(new QWidget())
,m_mainLayout(new QHBoxLayout())
,m_mainWidget(new QWidget())
{
    initUI();
}

void FlowLayoutWidget::initUI()
{
    // setAutoFillBackground(true);
    m_mainLayout->setAlignment(Qt::AlignHCenter);

    m_mainLayout->addWidget(m_contentWidget);

    m_contentWidget->setLayout(m_contentLayout);

    m_mainWidget->setLayout(m_mainLayout);

    // m_mainWidget->setAttribute(Qt::WA_TranslucentBackground);
    setWidget(m_mainWidget);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_StyledBackground);

    setStyleSheet("*{background-color: transparent;}");
}

void FlowLayoutWidget::addItem(QWidget *item)
{
    m_contentLayout->addWidget(item);
}

void FlowLayoutWidget::resizeEvent(QResizeEvent *event)
{
#if 0
    int maxHorCount = (event->size().width() - m_contentLayout->horizontalSpacing()) / (m_itemWidth + m_contentLayout->horizontalSpacing());
    int curContentWidth = maxHorCount * m_itemWidth + (maxHorCount + 1) * m_contentLayout->horizontalSpacing();
    m_contentWidget->setFixedWidth(curContentWidth);
    m_contentWidget->setFixedHeight(m_contentLayout->heightForWidth(curContentWidth));
    m_mainWidget->setFixedSize(event->size().width(), m_contentWidget->height());
    QScrollArea::resizeEvent(event);
#endif
}