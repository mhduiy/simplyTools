//
// Created by mhduiy on 2023/7/11.
//

#ifndef SIMPLYTOOLS_SIMPLYTRANSLATEWIDGET_H
#define SIMPLYTOOLS_SIMPLYTRANSLATEWIDGET_H
#include <QWidget>
#include <QLabel>
#include "TranslateTool.h"
#include <QGroupBox>
#include <QTextEdit>
#include <QComboBox>
#include <QVector>
#include "customComponents/MButton.h"
#include "customComponents/MNotificationBox.h"
#include "customComponents/MDialog.h"

const QVector<QPair<QString, QString>> srcTypeMap {
        {"自动检测", "auto"},
        {"中文", "zh"},
        {"繁体中文", "cht"},
        {"英语", "en"},
        {"日语", "jp"},
        {"粤语", "yue"},
        {"文言文", "wyw"},
        {"韩语", "kor"},
        {"法语", "fra"},
        {"德语", "de"},
        {"俄语", "ru"},
        {"西班牙语", "spa"}
};
const QVector<QPair<QString, QString>> tarTypeMap {
        {"中文", "zh"},
        {"繁体中文", "cht"},
        {"英语", "en"},
        {"日语", "jp"},
        {"粤语", "yue"},
        {"文言文", "wyw"},
        {"韩语", "kor"},
        {"法语", "fra"},
        {"德语", "de"},
        {"俄语", "ru"},
        {"西班牙语", "spa"}
};

class simplyTranslateWidget : public QWidget{
    Q_OBJECT
public:
    explicit simplyTranslateWidget(QWidget *parent = nullptr);
    ~simplyTranslateWidget() override;
private:
    void initUI();
public:
    void keyPressEvent(QKeyEvent* event)override;

protected:
    void showEvent(QShowEvent *event)override;

private slots:
    void on_btn_paste_clicked();

    void on_btn_tran_clicked();

    void on_btn_clear_clicked();

    void on_btn_copy_clicked();

    void on_btn_exchange_clicked();

    void on_btn_setUserInfo_clicked();


private:

    TranslateTool *translatetool;

    bool isFirstShow = true;

    QComboBox *srcTypeBox = nullptr;
    QComboBox *tarTypeBox = nullptr;
    MButton *exchangeBtn = nullptr;
    MButton *setUserInfoBtn = nullptr;

    QGroupBox *tranFromBox = nullptr;
    QGroupBox *tranToBox = nullptr;
    QTextEdit *ed_tranTo = nullptr;
    QTextEdit *ed_tranFrom = nullptr;

    MButton *pasteBtn = nullptr;
    MButton *tranBtn = nullptr;
    MButton *clearBtn = nullptr;
    MButton *copyBtn = nullptr;

    MNotificationBox *mNotificationBox = nullptr;

    MDialog *setInfoDialog = nullptr;
};

#endif //SIMPLYTOOLS_SIMPLYTRANSLATEWIDGET_H
