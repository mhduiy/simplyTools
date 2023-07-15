//
// Created by mhduiy on 2023/7/15.
//

#ifndef SIMPLYTOOLS_MDIALOG_H
#define SIMPLYTOOLS_MDIALOG_H

#include <QDialog>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include "customComponents/MButton.h"

class MDialog : public QDialog{
    Q_OBJECT
public:
    explicit MDialog(QWidget* parent = nullptr);
    ~MDialog()override;
    void initUI();
    /**
     *
     * @param label  标签
     * @param defaultStr  输入框默认值
     * @param tipStr  输入框提示
     * @return 输入框id
     */
    int addItem(const QString &label, const QString &defaultStr = "", const QString &tipStr = "");
    /**
     *
     * @param id
     * @return 获取指定id的输入框的数据
     */
    QString getItemInfo(int id);
    /**
     *
     * @param label
     * @return 获取指定label文字的输入框数据
     */
    QString getItemInfo(const QString& label);

    void setLabelById(const QString& label, int id = 0);
    void setDefaultStrById(const QString& defaultStr, int id = 0);
    void setTipById(const QString& tipStr, int id = 0);

    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();
    int exec()override;

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    QVector<QLabel*> labelVector;
    QVector<QLineEdit*> lineEditVector;

    QWidget* findMainWindow(QObject *obj);

    QWidget *mainWindow = nullptr;
    QGridLayout *mainLayout = nullptr;

    MButton *cancelBtn = nullptr;
    MButton *confirmBtn = nullptr;
};


#endif //SIMPLYTOOLS_MDIALOG_H
