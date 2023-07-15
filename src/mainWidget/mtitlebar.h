#ifndef MTITLEBAR_H
#define MTITLEBAR_H

#include <QWidget>
#include "customComponents/MButton.h"
#include <QLabel>
#include <QIcon>

class MTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit MTitleBar(QWidget *parent = nullptr);
    void closeWindow();
    void minWindow();
    void fixWindow();
    void setWindowTitle(const QString& title);
    void setWindowIcon(const QIcon& icon);

protected:
    void showEvent(QShowEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QWidget *findMainWindow(QObject *obj);

private:
    MButton *fixBtn = nullptr;
    MButton *minBtn = nullptr;
    MButton *closeBtn = nullptr;

    QLabel *titleLabel = nullptr;
    QLabel *iconLabel = nullptr;

    QWidget *mainWindow = nullptr;

    bool isPressed = false;
    QPoint tPos = QPoint(0,0);
};

#endif // MTITLEBAR_H
