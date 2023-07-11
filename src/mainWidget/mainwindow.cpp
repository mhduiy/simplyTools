#include "mainwindow.h"
#include "customComponents/MButton.h"
#include "customComponents/MSidebar.h"
#include <QLayout>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
     auto *main = new QWidget;
     QLayout *mainLayout = new QHBoxLayout(main);
     auto *sidebar = new MSidebar();
     mainLayout->addWidget(sidebar);
     mainLayout->addWidget(new MButton("Hello"));

    sidebar->addWidgetItem("simply翻译", QIcon(":/translate.png"));
    sidebar->addWidgetItem("屏幕截图", QIcon(":/screenShot.png"));
    sidebar->addWidgetItem("B站实时数据", QIcon(":/bilibiliData.png"));

    statusBar()->hide();
    setCentralWidget(main);
    this->centralWidget()->layout()->setMargin(0);
}

MainWindow::~MainWindow()
{

}

