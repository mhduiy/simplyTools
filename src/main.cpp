#include "mainWidget/mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QLoggingCategory>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QMap<int, QString>>("QMap<int, QString>");
    MainWindow w;

    a.setWindowIcon(QIcon(":/appIcon.png"));
    a.setApplicationName("simplyTools");
    a.setApplicationVersion("1.0");

    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);  //允许输出调试信息
    QApplication::setStyle(QStyleFactory::create("Fusion"));    // 应用Qt默认的样式, 屏蔽其他样式

    w.resize(600,450);

    // 移动到中间位置
    QDesktopWidget *desktop=QApplication::desktop();
    w.move((desktop->width()-w.width())/2, (desktop->height()-w.height())/2);

    w.show();
    return QApplication::exec();
}
