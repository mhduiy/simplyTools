//
// Created by mhduiy on 2023/7/11.
//

#ifndef SIMPLYTOOLS_MSIDEBAR_H
#define SIMPLYTOOLS_MSIDEBAR_H

#include <QWidget>
#include <QListWidget>
#include "MButton.h"
#include <QTimer>

class MSidebar : public QWidget{
Q_OBJECT
public:
    explicit MSidebar(QWidget *parent = nullptr);
    void addWidgetItem(const QString &text, const QIcon& icon);
protected:
    void showEvent(QShowEvent *event)override;
public slots:
    void foldPage();
private:
    // 初始化界面
    void initUI();
    bool isFolded = false;
    QListWidget *listWidget = nullptr;
    QPushButton *foldBtn = nullptr;
    QTimer animationTimer;
    void moveWidget();

    int cutX = 0;
    int tarX = 0;

    bool isFirstShow = true;
};

#endif //SIMPLYTOOLS_MSIDEBAR_H
