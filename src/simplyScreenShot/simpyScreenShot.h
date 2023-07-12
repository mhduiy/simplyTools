//
// Created by mhduiy on 2023/7/12.
//

#ifndef SIMPLYTOOLS_SIMPYSCREENSHOT_H
#define SIMPLYTOOLS_SIMPYSCREENSHOT_H
#include <QWidget>
#include "customComponents/MButton.h"
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QTimer>
#include "MFullWidget.h"

class SimpyScreenShot : public QWidget{
    Q_OBJECT
public:
    explicit SimpyScreenShot(QWidget *parent = nullptr);

private:
    void initUI();
    void screenShotOperator();
    void colorPickerOperator();
    void copyImageOperator();
    void saveImageOperator();
    void copyColorOperator();
    void showColorPicker();

protected:
    void mousePressEvent(QMouseEvent *event)override;
    void showEvent(QShowEvent *event)override;

private:
    QLabel *imageDisPlay = nullptr;         // 显示截图
    MButton *copyImageBtn = nullptr;        // 复制截图
    MButton *saveImageBtn = nullptr;        // 保存图片
    MButton *startScreenShotBtn = nullptr;  // 屏幕截图
    MButton *startColorPicker = nullptr;    // 取色器
    QLabel *colorDis = nullptr;             // 显示取到的颜色
    QLineEdit *colorValue = nullptr;        // 显示颜色值
    MButton *copyColorValueBtn = nullptr;   // 复制颜色值

    QString strDecimalValue, strHex;

    void exitColorWidget();

    QPixmap pixmap;
    QTimer timer;   //用于颜色实时获取

    MFullWidget *showImageWidget = nullptr;
    QLabel *showScreenImageLabel = nullptr;
    QWidget *showColorBox = nullptr;
    QLabel *colorLabelInDialog = nullptr;
    QLabel *posLabelInDialog = nullptr;
    QLabel *colorDisInDialog = nullptr;
    QColor cutColor;    //当前选择的颜色
    QWidget *mainWindow = nullptr;
};


#endif //SIMPLYTOOLS_SIMPYSCREENSHOT_H
