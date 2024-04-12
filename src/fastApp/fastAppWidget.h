//
// Created by mhduiy-123 on 23-8-8.
//

#ifndef SIMPLYTOOLS_FASTAPPWIDGET_H
#define SIMPLYTOOLS_FASTAPPWIDGET_H

#include "fastApp/FastAppItem.h"
#include <QWidget>
#include <QVector>
#include <QPushButton>
#include "FlowLayoutWidget.h"
#include "FastAppWoker.h"

class FastAppWidget : public QWidget{
    Q_OBJECT
public:
    explicit FastAppWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void onAddFastAppBtnClicked();
    void onEditFastAppBtnClicked();

private:
    QVector<FastAppItem*> m_fastAppItems;
    QPushButton *m_editFastAppBtn;
    QPushButton *m_addFastAppBtn;
    FlowLayoutWidget *m_mainWidget = nullptr;

    FastAppWorker *m_worker = nullptr;
};


#endif //SIMPLYTOOLS_FASTAPPWIDGET_H
