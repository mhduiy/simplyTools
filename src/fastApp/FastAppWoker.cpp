#include "FastAppWoker.h"

FastAppWorker::FastAppWorker(QObject *parent)
:QObject(parent)
,m_dialog(new MDialog(qobject_cast<QWidget*>(parent)))
,m_dialogWidget(new QWidget())
,m_tabSwitchButton(new MTabSwitchButton())
,m_appIcon(new QLabel())
,m_appNameEdit(new MLineEdit())
,m_appDescribtionEdit(new MLineEdit())
,m_appWidget(new QWidget())
,m_appPathEdit(new MLineEdit())
,m_appArgsEdit(new MLineEdit())
,m_cmdWidget(new QWidget())
,m_cmdEdit(new MLineEdit())
,m_dbusWidget(new QWidget())
,m_stackedWidget(new QStackedWidget())
{
    m_tabSwitchButton->addItem("启动应用");
    m_tabSwitchButton->addItem("执行命令");
    m_tabSwitchButton->addItem("运行Dbus");
    
    m_appNameEdit->setTipText("快捷应用名称");
    m_appDescribtionEdit->setTipText("描述");
    m_appPathEdit->setTipText("可执行文件路径");
    m_appArgsEdit->setTipText("启动参数");
    m_cmdEdit->setTipText("执行命令");

    auto *mainLayout = new QVBoxLayout(m_dialogWidget);

    auto *appLayout = new QVBoxLayout(m_appWidget);
    auto *cmdLayout = new QVBoxLayout(m_cmdWidget);
    auto *dbusLayout = new QVBoxLayout(m_dbusWidget);

    auto *tabHLayout = new QHBoxLayout();
    tabHLayout->setAlignment(Qt::AlignHCenter);
    tabHLayout->setSpacing(0);
    tabHLayout->setMargin(0);
    tabHLayout->addWidget(m_tabSwitchButton);

    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    appLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    appLayout->setSpacing(0);
    appLayout->setMargin(0);
    
    cmdLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    cmdLayout->setSpacing(0);
    cmdLayout->setMargin(0);

    dbusLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    dbusLayout->setSpacing(0);
    dbusLayout->setMargin(0);

    appLayout->addWidget(m_appPathEdit);
    appLayout->addWidget(m_appArgsEdit);

    cmdLayout->addWidget(m_cmdEdit);

    dbusLayout->addWidget(new QLabel("开发中..."));

    m_stackedWidget->addWidget(m_appWidget);
    m_stackedWidget->addWidget(m_cmdWidget);
    m_stackedWidget->addWidget(m_dbusWidget);

    mainLayout->addLayout(tabHLayout);;
    mainLayout->addWidget(m_appIcon);
    mainLayout->addWidget(m_appNameEdit);
    mainLayout->addWidget(m_appDescribtionEdit);
    mainLayout->addWidget(m_stackedWidget);

    m_dialog->addWidget(m_dialogWidget);

    connect(m_tabSwitchButton, QOverload<int>::of(&MTabSwitchButton::currentIndexChanged), m_stackedWidget, &QStackedWidget::setCurrentIndex);
}

void FastAppWorker::showDialog()
{
    m_dialog->exec();
}