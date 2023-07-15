//
// Created by mhduiy on 2023/7/14.  已弃用该类
//


/********** 已弃用该类 ********/
#ifndef SIMPLYTOOLS_SETINFODIALOG_H
#define SIMPLYTOOLS_SETINFODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "customComponents/MButton.h"
#include <QSettings>

class SetInfoDialog : public QWidget{
    Q_OBJECT
public:
    explicit SetInfoDialog(QWidget *parent = nullptr);
    void setIniInfo();

signals:
    void exitDialog(bool isCancel = true);
private:
    MButton *confirmBtn = nullptr;
    MButton *cancelBtn = nullptr;

    QLineEdit *sessdataEdit = nullptr;
    QLineEdit *bili_jctEdit = nullptr;
    QLineEdit *uidEdit = nullptr;

    QWidget *mainWidget = nullptr;

    QSettings *settings = nullptr;
};


#endif //SIMPLYTOOLS_SETINFODIALOG_H
