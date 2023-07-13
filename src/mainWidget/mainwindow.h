#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "customComponents/MButton.h"
#include "customComponents/MSidebar.h"
#include "simplyTranslate/simplyTranslateWidget.h"
#include "simplyScreenShot/simpyScreenShot.h"
#include "bilibiliData/bilibiliDataWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event)override;
    void resizeEvent(QResizeEvent *event) override;

private:
    MSidebar *sidebar = nullptr;
    QStackedWidget *stackedWidget = nullptr;

    simplyTranslateWidget *translateWidget = nullptr;
    SimpyScreenShot *simpyScreenShot = nullptr;
    BilibiliDataWidget *bilibiliDataWidget = nullptr;

};
#endif // MAINWINDOW_H
