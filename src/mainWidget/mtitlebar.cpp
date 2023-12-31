#include "mtitlebar.h"
#include <QLayout>
#include <QGuiApplication>
#include <QMouseEvent>

MTitleBar::MTitleBar(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignJustify);
    mainLayout->setMargin(0);

    iconLabel = new QLabel("图标");
    titleLabel = new QLabel("title");

    QFont font = titleLabel->font();
    font.setPixelSize(15);
    titleLabel->setFont(font);

    iconLabel->setScaledContents(true);

    fixBtn = new MButton("");
    minBtn = new MButton("");
    closeBtn = new MButton("");

    fixBtn->setCategory(MBtn_ordinary);
    minBtn->setCategory(MBtn_ordinary);
    closeBtn->setCategory(MBtn_warning);

    fixBtn->setFixedSize(30,30);
    minBtn->setFixedSize(30,30);
    closeBtn->setFixedSize(30,30);
    iconLabel->setFixedSize(30,30);

    fixBtn->setIcon(QIcon(":/fixWindow.png"));
    minBtn->setIcon(QIcon(":/minWindow.png"));
    closeBtn->setIcon(QIcon(":/closeWindow.png"));

    fixBtn->setCheckable(true);
    fixBtn->setChecked(true);

    fixBtn->setToolTip("固定这个窗口");
    minBtn->setToolTip("收起这个窗口");
    closeBtn->setToolTip("关掉这个窗口");

    auto *operatorLayout = new QHBoxLayout();
    operatorLayout->addStretch();
    operatorLayout->addWidget(fixBtn);
    operatorLayout->addWidget(minBtn);
    operatorLayout->addWidget(closeBtn);

    auto *iconLayout = new QHBoxLayout();
    iconLayout->addWidget(iconLabel);
    iconLayout->addStretch();

    titleLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setAlignment(Qt::AlignCenter);

    titleLabel->setAlignment(Qt::AlignHCenter);

    mainLayout->addLayout(iconLayout, 1);
    mainLayout->addStretch(1);
    mainLayout->addWidget(titleLabel, 1, Qt::AlignHCenter);
    mainLayout->addStretch(1);
    mainLayout->addLayout(operatorLayout, 1);

    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedHeight(30);

    connect(fixBtn, &QPushButton::clicked, this, &MTitleBar::fixWindow);
    connect(minBtn, &QPushButton::clicked, this, &MTitleBar::minWindow);
    connect(closeBtn, &QPushButton::clicked, this, &MTitleBar::closeWindow);
}

void MTitleBar::closeWindow()
{
    mainWindow->close();
}

void MTitleBar::minWindow()
{
    mainWindow->showMinimized();
}

void MTitleBar::fixWindow()
{
    auto flags = mainWindow->windowFlags();
    if(flags & Qt::WindowStaysOnTopHint) {  //当前是窗口置顶
        // 取消窗口置顶
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~Qt::WindowStaysOnTopHint);
        fixBtn->setIcon(QIcon(":/unFixWindow.png"));
        mainWindow->show();
        fixBtn->setChecked(false);
    }
    else {
        // 设置窗口置顶
        mainWindow->setWindowFlags(mainWindow->windowFlags() | Qt::WindowStaysOnTopHint);
        fixBtn->setIcon(QIcon(":/fixWindow.png"));
        mainWindow->show();
        fixBtn->setChecked(true);
    }
}

void MTitleBar::setWindowTitle(const QString &title)
{
    titleLabel->setText(title);
}

void MTitleBar::setWindowIcon(const QIcon &icon)
{
    iconLabel->setPixmap(icon.pixmap(30,30));

}

void MTitleBar::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if(mainWindow == nullptr) {
        mainWindow = findMainWindow(this);
        this->setWindowIcon(qApp->windowIcon());
        this->setWindowTitle(qApp->applicationName());
    }
}

void MTitleBar::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    tPos = event->globalPos() - mainWindow->geometry().topLeft();
}

void MTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void MTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    mainWindow->move(event->globalPos() - tPos);
}

QWidget *MTitleBar::findMainWindow(QObject *obj)
{
    if(obj == nullptr) {
        return nullptr;
    }
    if(strcmp(obj->metaObject()->className(), "MainWindow") == 0) {
        return qobject_cast<QWidget*>(obj);
    }
    return findMainWindow(obj->parent());
}
