#include "mainWidget/mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);  //允许输出调试信息

    w.resize(700,400);

    // 移动到中间位置
    QDesktopWidget *desktop=QApplication::desktop();
    w.move((desktop->width()-w.width())/2, (desktop->height()-w.height())/2);

    w.show();
    return QApplication::exec();
}
