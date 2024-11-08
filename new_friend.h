#ifndef NEW_FRIEND_H
#define NEW_FRIEND_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>
#include <QJsonArray>

namespace Ui {
class New_friend;
}

class New_friend : public QWidget
{
    Q_OBJECT

public:
    explicit New_friend(QString usernameA,QWidget *parent = nullptr);
    ~New_friend();
    QTcpSocket *mSocket; //网络通讯对象


private:
    Ui::New_friend *ui;
    QString m_usernameA="NULL";
private slots:
    void slot_read();
    void slot_send();
    void on_renew_btn_clicked();
    void addFriendItem(const QString& userAid);
    void accept_friend(const QString& userAid);
    void reject_other(const QString& userAid);
};

#endif // NEW_FRIEND_H
