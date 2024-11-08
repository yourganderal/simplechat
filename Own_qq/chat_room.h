#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H

#include"add_new_widget.h"
#include <QWidget>
#include <QDebug>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBoxLayout>
#include <QListWidgetItem>
#include <QComboBox>
#include <QTextEdit>
#include <QFontDatabase> //获取系统字体，大小
#include <QColorDialog>
#include <QTimer>


namespace Ui {
class Chat_room;
}

class Chat_room : public QWidget
{
    Q_OBJECT

public:
    explicit Chat_room(QString username,QWidget *parent = nullptr);
    ~Chat_room();
    QTcpSocket *mSocket;

private slots:
    void addFriendItem(const QString& userAid);
    void on_add_new_btn_clicked(); //加好友按钮的点击
    void slot_read();  //读取服务端发过来的数据
    void onItemClicked(QListWidgetItem* item); //点击聊天人
    void on_renew_Btn_clicked(); //点击更新按钮
    //void sendMessage(const QString &message,const QFont &font,const QColor &color); //发送消息，带格式；
    void on_send_btn_clicked();
    void on_size_Box_currentIndexChanged(int Fontsize);
    void initFontSizeBox();  //初始化字体大小
    void initFontComboBox();  //初始化字体
    void sendStyleText();  //发送带样式的信息
    void read_message_slot(const QString &usernameA,const QString &usernameB);//发送获取对方的消息的请求
    void read_message();//获取对方发送来的消息

    //void comboBoxSlot(const QString )

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Size_Btn_clicked(bool checked);

    void on_I_Btn_clicked(bool checked);

    void on_under_line_Btn_clicked(bool checked);

    void on_Color_Btn_clicked(bool checked);

    void on_Color_Btn_clicked();

private:
    Ui::Chat_room *ui;
    QComboBox *size_Box;
    QString m_username="NULL";
    Add_new_widget* add_new_window=nullptr; //添加新联系人的窗口
    void get_friendname(const QString usernameB);
};

#endif // CHAT_ROOM_H
