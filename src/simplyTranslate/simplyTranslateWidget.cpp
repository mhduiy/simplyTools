//
// Created by mhduiy on 2023/7/11.
//

#include "simplyTranslateWidget.h"
#include <QLayout>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QFile>

simplyTranslateWidget::simplyTranslateWidget(QWidget *parent) : QWidget(parent){
    initUI();

    // 加载样式表
    QFile file(":/translate.qss");
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()) {
        this->setStyleSheet(file.readAll());
    }
    file.close();
}

void simplyTranslateWidget::initUI() {
    translatetool = new TranslateTool(this);
    tranFromBox = new QGroupBox();
    tranToBox = new QGroupBox();
    ed_tranFrom = new QTextEdit();
    ed_tranTo = new QTextEdit();
    tranOptionBtn = new MButton("中文->英文");
    pasteBtn = new MButton("粘贴");
    tranBtn = new MButton("翻译");
    clearBtn = new MButton("清除");
    copyBtn = new MButton("复制");

    auto *mainLayout = new QHBoxLayout(this);
    auto *edLayout = new QVBoxLayout();
    auto *btnLayout = new QVBoxLayout();

    tranFromBox->setLayout(new QVBoxLayout);
    tranFromBox->layout()->addWidget(ed_tranFrom);
    tranToBox->setLayout(new QVBoxLayout);
    tranToBox->layout()->addWidget(ed_tranTo);

    tranFromBox->setTitle("在这里输入你要翻译的内容");
    tranToBox->setTitle("翻译结果");

    edLayout->addWidget(tranFromBox);
    edLayout->addWidget(tranToBox);

    btnLayout->addWidget(tranOptionBtn);
    btnLayout->addWidget(tranBtn);
    btnLayout->addWidget(clearBtn);
    btnLayout->addWidget(pasteBtn);
    btnLayout->addWidget(copyBtn);

    tranBtn->setCategory(MBtn_suggested);
    clearBtn->setCategory(MBtn_warning);

    mainLayout->addLayout(edLayout);
    mainLayout->addLayout(btnLayout);

//    mainWindow

    connect(tranOptionBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_FormAndTo_clicked);
    connect(pasteBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_paste_clicked);
    connect(tranBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_tran_clicked);
    connect(clearBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_clear_clicked);
    connect(copyBtn, &MButton::clicked, this, &simplyTranslateWidget::on_btn_copy_clicked);

    //链接显示翻译结果
    connect(translatetool,&TranslateTool::translateOK,this,[=](QString res){
        ed_tranTo->setText(res);
        tranToBox->setTitle("翻译结果");
    });

    TranStyle = new QVector<QString>    //显示翻译类型
            {
                    "中文->英文",
                    "英文->中文"
            };

    tranOptionBtn->setText(TranStyle->value(0));

    TranStylecode = new QVector<QPair<QString,QString>>
            {
                    QPair<QString,QString>{"zh","en"},
                    QPair<QString,QString>{"en","zh"}
            };

    qDebug() << QSslSocket::supportsSsl()
             << QSslSocket::sslLibraryBuildVersionString()
             << QSslSocket::sslLibraryVersionString();
}

simplyTranslateWidget::~simplyTranslateWidget()
{
    delete TranStyle;
    delete TranStylecode;
}

void simplyTranslateWidget::keyPressEvent(QKeyEvent *event)//绑定按键
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Return)
    {
        this->on_btn_tran_clicked();
    }
}

void simplyTranslateWidget::on_btn_paste_clicked() //粘贴
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    ed_tranFrom->clear();
    ed_tranFrom->setText(clipboard->text());
}

void simplyTranslateWidget::on_btn_tran_clicked()  //翻译
{
    //获取翻译内容
    QString src = ed_tranFrom->toPlainText();
    int curIndex = isZHToeEN ? 0 : 1;
    if(src.isEmpty())
    {
        return;
    }
    if(!(TranStylecode->size() > curIndex))
    {
        QMessageBox::warning(this,"错误","curIndex error");
    }
    tranToBox->setTitle("翻译中...");
    translatetool->TranslateFromBaidu(src,TranStylecode->value(curIndex).first,TranStylecode->value(curIndex).second);
}

void simplyTranslateWidget::on_btn_clear_clicked() //清除
{
    ed_tranTo->clear();
    ed_tranFrom->clear();
}

void simplyTranslateWidget::on_btn_copy_clicked()  //复制
{
    if(ed_tranTo->toPlainText().isEmpty()) {
        mNotificationBox->sendMsg("翻译结果为空", QIcon(":/warningIcon.png"));
        return;
    }
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ed_tranTo->toPlainText());
    mNotificationBox->sendMsg("翻译结果成功复制到剪切板", QIcon(":/successIcon.png"));
}


void simplyTranslateWidget::on_btn_FormAndTo_clicked()
{
    if(tranOptionBtn->text() == TranStyle->value(0)) {
        tranOptionBtn->setText(TranStyle->value(1));
        isZHToeEN = false;
    }
    else {
        tranOptionBtn->setText(TranStyle->value(0));
        isZHToeEN = true;
    }
}

void simplyTranslateWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    if(mNotificationBox == nullptr) {
        mNotificationBox = new MNotificationBox(this);
    }
}
