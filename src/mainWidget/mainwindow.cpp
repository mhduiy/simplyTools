#include "mainwindow.h"
#include <QLayout>
#include <QStatusBar>
#include <QBitmap>
#include <QPainter>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);    //设置窗口置顶
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

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
    sidebar->addWidgetItem("快捷应用", QIcon(":/bilibiliData.png"));

    translateWidget = new simplyTranslateWidget();
    simpyScreenShot = new SimpyScreenShot();
    bilibiliDataWidget = new BilibiliDataWidget();
    fastAppWidget = new FastAppWidget();

    stackedWidget->addWidget(translateWidget);
    stackedWidget->addWidget(simpyScreenShot);
    stackedWidget->addWidget(bilibiliDataWidget);
    stackedWidget->addWidget(fastAppWidget);

    connect(sidebar, &MSidebar::currentIndexChanged, [this](int index){
        this->stackedWidget->setCurrentIndex(index);
    });

    QLayout *mainWindowLayout = new QHBoxLayout(this);
    mainWindowLayout->addWidget(main);
    mainWindowLayout->setContentsMargins(15,3,15,3);
    sidebar->raise();  // 控件置顶
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
