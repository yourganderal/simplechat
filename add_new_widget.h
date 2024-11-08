#ifndef ADD_NEW_WIDGET_H
#define ADD_NEW_WIDGET_H

#include"new_friend.h"
#include <QWidget>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

namespace Ui {
class Add_new_widget;
}

class Add_new_widget : public QWidget
{
    Q_OBJECT

public:
    explicit Add_new_widget(QString username_A,QWidget *parent = nullptr);
    ~Add_new_widget();
    QTcpSocket *mSocket;  //网络通讯对象

private slots:
    void on_add_btn_clicked();
    void slot_read();

    void on_new_friends_clicked();

private:
    Ui::Add_new_widget *ui;
    QString myusername="NULL";
    New_friend* new_friend_window=nullptr;  //好友申请的窗口
};

#endif // ADD_NEW_WIDGET_H
