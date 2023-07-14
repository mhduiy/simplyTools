#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "customComponents/MButton.h"
#include "customComponents/MSidebar.h"
#include "simplyTranslate/simplyTranslateWidget.h"
#include "simplyScreenShot/simpyScreenShot.h"
#include "bilibiliData/bilibiliDataWidget.h"
#include "mtitlebar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;

protected:
    void showEvent(QShowEvent *event)override;
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent* event) override;

private:
    MSidebar *sidebar = nullptr;
    QStackedWidget *stackedWidget = nullptr;

    simplyTranslateWidget *translateWidget = nullptr;
    SimpyScreenShot *simpyScreenShot = nullptr;
    BilibiliDataWidget *bilibiliDataWidget = nullptr;
    MTitleBar *titleBar;
};
#endif // MAINWINDOW_H
