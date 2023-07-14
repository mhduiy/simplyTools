#include "mainwindow.h"
#include <QLayout>
#include <QStatusBar>
#include <QBitmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);    //设置窗口置顶
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setWindowOpacity(0.9);

    auto *main = new QWidget;
    QLayout *mainLayout = new QVBoxLayout(main);
    sidebar = new MSidebar(this);
    stackedWidget = new QStackedWidget();
    titleBar = new MTitleBar(this);

    sidebar->move(0, 0);
//    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(stackedWidget);

    sidebar->addWidgetItem("simply翻译", QIcon(":/translate.png"));
    sidebar->addWidgetItem("屏幕截图", QIcon(":/screenShot.png"));
    sidebar->addWidgetItem("B站实时数据", QIcon(":/bilibiliData.png"));

    translateWidget = new simplyTranslateWidget();
    simpyScreenShot = new SimpyScreenShot();
    bilibiliDataWidget = new BilibiliDataWidget();
    stackedWidget->addWidget(translateWidget);
    stackedWidget->addWidget(simpyScreenShot);
    stackedWidget->addWidget(bilibiliDataWidget);

    connect(sidebar, &MSidebar::currentIndexChanged, [this](int index){
        this->stackedWidget->setCurrentIndex(index);
    });

    statusBar()->hide();
    setCentralWidget(main);
    this->centralWidget()->layout()->setContentsMargins(15,3,15,3);

    sidebar->raise();  // 控件置顶

    this->setStyleSheet("MainWindow{ background-color: #ffffff; border-radius: 10px;}");
}

void MainWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    sidebar->setFixedHeight(this->geometry().height());
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

MainWindow::~MainWindow()
= default;
