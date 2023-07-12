//
// Created by mhduiy on 2023/7/12.
//

#ifndef SIMPLYTOOLS_SIMPYSCREENSHOT_H
#define SIMPLYTOOLS_SIMPYSCREENSHOT_H
#include <QWidget>
#include "customComponents/MButton.h"
#include <QLabel>
#include <QLineEdit>

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

private:
    QLabel *imageDisPlay = nullptr;         // 显示截图
    MButton *copyImageBtn = nullptr;        // 复制截图
    MButton *saveImageBtn = nullptr;        // 保存图片
    MButton *startScreenShotBtn = nullptr;  // 屏幕截图
    MButton *startColorPicker = nullptr;    // 取色器
    QLabel *colorDis{};                       // 显示取到的颜色
    QLineEdit *colorValue{};                  // 显示颜色值
    MButton *copyColorValueBtn{};             // 复制颜色值
};


#endif //SIMPLYTOOLS_SIMPYSCREENSHOT_H
