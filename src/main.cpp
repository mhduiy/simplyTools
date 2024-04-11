#include "mainWidget/mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QLoggingCategory>
#include <QStyleFactory>
#include "global/globalSetting.h"
#include "simplyTranslate/TranslateTool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QMap<int, QString>>("QMap<int, QString>");
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);  //允许输出调试信息
    QApplication::setStyle(QStyleFactory::create("Fusion"));    // 应用Qt默认的样式, 屏蔽其他样式
    a.setWindowIcon(QIcon(":/appIcon.png"));
    a.setApplicationName("simplyTools");
    a.setApplicationVersion("1.0");

    globalSetting::getInstance(&a); // 创建设置类对象

    if (argc > 1) {
        QString from = "zh";
        QString to = "en";
        QString src = "";
        TranslateTool tool;
        if (argc == 2) {
            src = argv[1];
        } else if (argc == 4) {
            from = argv[1];
            to = argv[2];
            src = argv[3];
        } else {
            qWarning("参数数量错误");
            exit(EXIT_FAILURE);
        }
        QTimer::singleShot(100, [&](){
            tool.TranslateFromBaidu(src, from, to, true);
        });
        return a.exec();
    }
    
    MainWindow w;
    w.resize(700,500);

    // 移动到中间位置
    QDesktopWidget *desktop=QApplication::desktop();
    w.move((desktop->width()-w.width())/2, (desktop->height()-w.height())/2);

    w.show();
    return QApplication::exec();
}

// 添加一个App， 可以Dbus调用， 可以通过通过参数来启动