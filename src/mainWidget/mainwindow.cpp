#include "mainwindow.h"
#include <QLayout>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);    //设置窗口置顶

    setWindowOpacity(0.9);

    auto *main = new QWidget;
    QLayout *mainLayout = new QHBoxLayout(main);
    sidebar = new MSidebar(this);
    stackedWidget = new QStackedWidget();

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);

    sidebar->addWidgetItem("simply翻译", QIcon(":/translate.png"));
    sidebar->addWidgetItem("屏幕截图", QIcon(":/screenShot.png"));
    sidebar->addWidgetItem("B站实时数据", QIcon(":/bilibiliData.png"));

    translateWidget = new simplyTranslateWidget();
    stackedWidget->addWidget(translateWidget);
    stackedWidget->addWidget(new QWidget);
    stackedWidget->addWidget(new QWidget);

    connect(sidebar, &MSidebar::currentIndexChanged, [this](int index){
        this->stackedWidget->setCurrentIndex(index);
    });

    statusBar()->hide();
    setCentralWidget(main);
    this->centralWidget()->layout()->setMargin(0);
}

MainWindow::~MainWindow()
= default;