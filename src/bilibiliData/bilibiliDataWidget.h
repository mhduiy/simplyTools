//
// Created by mhduiy on 2023/7/13.
//

#ifndef SIMPLYTOOLS_BILIBILIDATAWIDGET_H
#define SIMPLYTOOLS_BILIBILIDATAWIDGET_H
#include <QWidget>
#include <QLabel>
#include "customComponents/MIcon.h"
#include "customComponents/MButton.h"
#include "customComponents/MNotificationBox.h"
#include "BiliBiliDataTool.h"
#include <QThread>
#include "setInfoDialog.h"
#include <QSettings>
#include "customComponents/MDialog.h"

class BilibiliDataWidget : public QWidget{
    Q_OBJECT
public:
    explicit BilibiliDataWidget(QWidget *parent = nullptr);
    void updateToolData();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void initUI();
    void initData();
    void updateBtnClicked();
    void setInfoBtnClicked();

    void showData(const QMap<int, QString>&);

    QWidget *findMainWindow(QObject *obj);

private:
    QLabel *headImageLabel = nullptr;

    QLabel *userNameLabel = nullptr;
    QLabel *uidLabel = nullptr;
    QLabel *levelLabel = nullptr;

    MButton *setInfoBtn = nullptr;
    MButton *updateBtn = nullptr;

    MIcon *coinCountLabel = nullptr;
    MIcon *followCountLabel = nullptr;
    MIcon *fanCountLabel = nullptr;
    MIcon *likeCountLabel = nullptr;
    MIcon *playCountLabel = nullptr;
    MIcon *readCountLabel = nullptr;

    MNotificationBox *mNotificationBox = nullptr;
    BiliBiliDataTool *biliBiliDataTool = nullptr;

    QThread *getBiliBiliDataThread = nullptr;

    bool isFirstShow = true;

    QWidget *mainWindow = nullptr;
    MDialog *setInfoDialog = nullptr;
};


#endif //SIMPLYTOOLS_BILIBILIDATAWIDGET_H
