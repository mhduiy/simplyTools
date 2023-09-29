#ifndef FLOWLAYOUTWIDGET_H
#define FLOWLAYOUTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <dflowlayout.h>

DWIDGET_USE_NAMESPACE

class FlowLayoutWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit FlowLayoutWidget(QWidget *parent = nullptr);
    void addItem(QWidget *item);
    void initUI();
    void setItemWidth(int width);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    DFlowLayout *m_contentLayout = nullptr;
    QWidget *m_contentWidget = nullptr;
    QWidget *m_mainWidget = nullptr;
    QHBoxLayout *m_mainLayout = nullptr;
    int m_itemWidth = 110;
};

#endif