//
// Created by mhduiy on 2023/7/15.
//

#include <QGraphicsBlurEffect>
#include "MDialog.h"
#include <QDebug>

MDialog::MDialog(QWidget *parent) : QDialog(parent){
    initUI();
}
void MDialog::initUI() {
    m_vLayout = new QVBoxLayout(this);
    auto *btnLayout = new QHBoxLayout();
    mainLayout = new QGridLayout();

    confirmBtn = new MButton("确认", MBtn_ordinary);
    cancelBtn = new MButton("取消", MBtn_warning);

    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(confirmBtn);

    m_vLayout->addLayout(mainLayout);
    m_vLayout->addLayout(btnLayout);

    setMinimumWidth(300);

    connect(confirmBtn, &MButton::clicked, this, &MDialog::on_confirmBtn_clicked);
    connect(cancelBtn, &MButton::clicked, this, &MDialog::on_cancelBtn_clicked);

}

MDialog::~MDialog() {
}


int MDialog::addItem(const QString &label, const QString &defaultStr, const QString &tipStr) {
    int total = labelVector.size();
    auto *_la = new QLabel(label);
    auto *_ed = new QLineEdit();
    _ed->setPlaceholderText(tipStr);
    _ed->setText(defaultStr);

    mainLayout->addWidget(_la, total, 0);
    mainLayout->addWidget(_ed, total, 1);

    labelVector.append(_la);
    lineEditVector.append(_ed);

    return total;
}

QString MDialog::getItemInfo(int id) {
    auto _ed = lineEditVector.value(id);
    if(_ed == nullptr) {
        return {};
    }
    return _ed->text();
}

QString MDialog::getItemInfo(const QString &label) {
    const QLineEdit *_ed = nullptr;
    foreach(auto &_lineEdit, lineEditVector) {
        if(_lineEdit->text() == label) {
            _ed = _lineEdit;
            break;
        }
    }
    if(_ed == nullptr) {
        return {};
    }
    return _ed->text();
}

void MDialog::setLabelById(const QString& label, int id) {
    if(id >= labelVector.size() || id < 0) {
        return;
    }
    labelVector.value(id)->setText(label);
}

void MDialog::setDefaultStrById(const QString& defaultStr, int id) {
    if(id >= lineEditVector.size() || id < 0) {
        return;
    }
    lineEditVector.value(id)->setText(defaultStr);
}

void MDialog::setTipById(const QString& tipStr, int id) {
    if(id >= lineEditVector.size() || id < 0) {
        return;
    }
    lineEditVector.value(id)->setPlaceholderText(tipStr);
}

void MDialog::on_confirmBtn_clicked() {
    this->accept();
}


void MDialog::on_cancelBtn_clicked() {
    this->reject();
}

void MDialog::addWidget(QWidget *widget)
{
    m_vLayout->insertWidget(0, widget);
}

QWidget *MDialog::findMainWindow(QObject *obj) {
    if(obj == nullptr) {
        return nullptr;
    }
    if(strcmp(obj->metaObject()->className(), "MainWindow") == 0) {
        return qobject_cast<QWidget*>(obj);
    }
    return findMainWindow(obj->parent());
}

void MDialog::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    if(mainWindow == nullptr) {
        mainWindow = findMainWindow(this->parent());
    }
    if(mainWindow != nullptr) {
        // 创建模糊效果
        auto *blurEffect = new QGraphicsBlurEffect(mainWindow);
        blurEffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint); // 设置性能提示
        blurEffect->setBlurRadius(20);
        mainWindow->setGraphicsEffect(blurEffect);
    }
}

void MDialog::closeEvent(QCloseEvent *event) {
    if(mainWindow != nullptr) {
        mainWindow->setGraphicsEffect(nullptr);
    }
    QDialog::closeEvent(event);
}

int MDialog::exec() {
    int ret = QDialog::exec();
    this->close();
    return ret;
}
