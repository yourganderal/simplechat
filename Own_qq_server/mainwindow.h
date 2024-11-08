#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "mythead.h"

#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QJsonArray>
#include <QMap>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleNewConnection();//处理新连接
    void readClientData();
private:
    Ui::MainWindow *ui;
    QTcpServer *mServer;
    int mPort;  //端口号
    QTcpSocket* mSocket;  //通讯套接字
    void ConnectDatebase1();//连接存储用户账号密码的数据库
    void ConnectDatebase2();//连接friendship数据库
    void ConnectDatebase3();//连接储存聊天记录的数据库
    bool checkUserCredentials(const QString &username, const QString &password); // 验证用户的凭证
    int checkisregister(const QString &username,const QString &password);   //验证用户注册 0-注册失败 1-注册成功 2-已有账号
    bool checkaddnewuser(const QString &usernameA,const QString &usernameB);   //验证加好友是否成功
    //bool checkadd_is_exist(const QString &usernameB);     //看要添加的好友是否存在
    bool checkUser_is_exist(const QString &username);   //查询用户是否在数据库1中
    bool checkUser_is_sendadd(const QString &usernameA,const QString &usernameB); //查询用户是否已经发送过好友申请
    void get_newfriends(const QString &usernameA);  //获取向用户A申请好友的用户
    void reject_others(const QString &usernameA,const QString &usernameB);//拒绝好友申请
    void accept_friends(const QString &usernameA,const QString &usernameB);//同意好友申请
    void get_friends(const QString &usernameB); //获取B的好友
    void get_friends_tochat(const QString &usernameA,const QString &usernameB);//添加好友到聊天数据库中
    void save_in_message(const QString &usernameA,const QString &usernameB,const QString &text); //3
    void read_message(const QString &usernameA,const QString &usernameB); //3

};
#endif // MAINWINDOW_H
