#ifndef WIDGET_H
#define WIDGET_H

#include "register.h"
#include "chat_room.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpSocket* mSocket;  //网络通讯对象

private slots:
    void on_Register_btn_clicked();
    void on_Login_btn_clicked();

    void slot_read(); //添加这个槽函数的申明
private:
    Ui::Widget *ui;
    Register *registerWindow=nullptr;   //注册窗口
    Chat_room *chat_room=nullptr;      //登录窗口
};
#endif // WIDGET_H
