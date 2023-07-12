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
#include "customComponents/MButton.h"
#include "customComponents/MNotificationBox.h"

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

    void on_btn_FormAndTo_clicked();

private:

    QVector<QString> *TranStyle;        //显示翻译类型
    QVector<QPair<QString,QString>> *TranStylecode;    //翻译类型

    TranslateTool *translatetool;

    bool isZHToeEN = true;  // 当前是中文到英文的翻译

    QGroupBox *tranFromBox = nullptr;
    QGroupBox *tranToBox = nullptr;
    QTextEdit *ed_tranTo = nullptr;
    QTextEdit *ed_tranFrom = nullptr;
    MButton *tranOptionBtn = nullptr;
    MButton *pasteBtn = nullptr;
    MButton *tranBtn = nullptr;
    MButton *clearBtn = nullptr;
    MButton *copyBtn = nullptr;

    MNotificationBox *mNotificationBox = nullptr;
};

#endif //SIMPLYTOOLS_SIMPLYTRANSLATEWIDGET_H
