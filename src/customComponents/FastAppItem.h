//
// Created by mhduiy-123 on 23-8-8.
//

#ifndef SIMPLYTOOLS_FASTAPPITEM_H
#define SIMPLYTOOLS_FASTAPPITEM_H

#include <QWidget>
#include <DFloatingButton>

DWIDGET_USE_NAMESPACE

class FastAppItem : public QWidget{
    Q_OBJECT
public:
    explicit FastAppItem(QWidget* parent = nullptr);

private:
    void initUI();
    DFloatingButton *dFloatingButton = nullptr;
};


#endif //SIMPLYTOOLS_FASTAPPITEM_H
