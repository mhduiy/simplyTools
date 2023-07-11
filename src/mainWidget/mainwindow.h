#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "customComponents/MButton.h"
#include "customComponents/MSidebar.h"
#include "simplyTranslate/simplyTranslateWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MSidebar *sidebar = nullptr;
    QStackedWidget *stackedWidget = nullptr;

    simplyTranslateWidget *translateWidget = nullptr;

};
#endif // MAINWINDOW_H
