//
// Created by mhduiy-123 on 23-8-8.
//

#ifndef SIMPLYTOOLS_FASTAPPITEM_H
#define SIMPLYTOOLS_FASTAPPITEM_H

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>

class FastAppItem : public QWidget{
    Q_OBJECT
public:
    explicit FastAppItem(QWidget* parent = nullptr);

    void setIcon(const QIcon& icon);

    void showOperatorBtn();
    void hideOperatorBtn();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void initUI();
    void initData();
    void initConnect();
    QPushButton *m_deleteBtn = nullptr;
    QPushButton *m_editBtn = nullptr;
    
    bool m_isHover;
    bool m_isPress;

    QPropertyAnimation *m_deleteBtnOpacityAni;
    QPropertyAnimation *m_editBtnOpacityAni;

    QPropertyAnimation *m_deleteBtnSizeAni;
    QPropertyAnimation *m_editBtnSizeAni;

    int m_defaultBtnWidthAndHeight = 22;
};


#endif //SIMPLYTOOLS_FASTAPPITEM_H
