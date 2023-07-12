//
// Created by mhduiy on 2023/7/12.
//

#ifndef SIMPLYTOOLS_MFULLWIDGET_H
#define SIMPLYTOOLS_MFULLWIDGET_H
#include <QWidget>

class MFullWidget : public QWidget{
    Q_OBJECT
public:
    explicit MFullWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event)override;
    void keyPressEvent(QKeyEvent *event)override;
signals:
    void leftMousePressed();
    void rightMousePressed();
    void escKeyPressed();
};


#endif //SIMPLYTOOLS_MFULLWIDGET_H
