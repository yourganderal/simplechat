#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QHostAddress>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    QTcpSocket *mSocket;  //网络通讯对象

private slots:
    void on_register_Cancel_btn_clicked();
    void slot_read();

    void on_register_Confirm_btn_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
