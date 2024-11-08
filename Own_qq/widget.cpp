#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket =new QTcpSocket;
    //连接服务器
    QString ip="192.168.31.135";
    mSocket->connectToHost(QHostAddress(ip),6666); //连接到主机
    if (mSocket->waitForConnected()) {
            QMessageBox::information(this, "连接成功", "已连接到服务器");
        } else {
            QMessageBox::warning(this, "连接错误", "无法连接到服务器");
        }
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(slot_read()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Register_btn_clicked()
{
    qDebug()<<"Register button clicked";
    //当Register 按钮被点击 ，检查注册窗口是否已经存在
    if(registerWindow == nullptr){
        registerWindow = new Register(nullptr);   //如果没有创建一个新窗口
        connect(registerWindow,&QWidget::destroyed,this,[this](){
            registerWindow = nullptr;  //清理指针
        });
    }else{
        qDebug() << "Showing existing Register window.";
    }
    registerWindow->show();  //显示新窗口
    registerWindow->raise();  // 把窗口放到最前面
    registerWindow->activateWindow(); // 激活窗口以便能够接收输入

}

void Widget::on_Login_btn_clicked()
{
    //传一个int类型用于服务器对收到的数的操作方式
    int way = 0;
    //获取用户输入的数据
    QString Username =ui->User_line->text();
    QString Usercode =ui->Code_line->text();
    //QString Way = way.text();
    //构建json串
    QJsonObject jsonobject;
    jsonobject["username"]=Username;
    jsonobject["usercode"]=Usercode;
    jsonobject["way"]=way;
    //将 json 对象转换为字符串
    QJsonDocument jsodoc(jsonobject);
    QByteArray jsonData = jsodoc.toJson();
    //发送 json 数据到服务器
    if(mSocket && mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();   //?

        //QEventLoop loop;
        //QTimer::singleShot(100,&loop,SLOT(quit()));
        //loop.exec();
        slot_read();

    }else{
        qDebug()<< "Socket is not connect";
    }

}
void Widget::slot_read()
{
    //先确保有数据可读
    if(mSocket->bytesAvailable()==0){
        qDebug()<<"没有读到数据。";
        return ;
    }

    // 实现 slot_read() 函数
       QByteArray data = mSocket->readAll();
       qDebug() << "Received data:" << data;

       // 解析 JSON 数据
       QJsonDocument jsondoc = QJsonDocument::fromJson(data);
       if (!jsondoc.isObject()) {
           qDebug() << "接收到 invalid JSON data";
           return;
       }
       QJsonObject jsonObject = jsondoc.object();
       QString status = jsonObject["status"].toString();  // 获取响应状态

       // 根据响应状态进行处理
       if (status == "success") {
           //QString login_username= jsonObject["username"].toString();
           QMessageBox::information(this, "登录", "登录成功");
           // 此处可以添加代码跳转到另一个窗口或执行其他操作
           if(chat_room == nullptr){
               qDebug()<<"login_username: "<<ui->User_line->text();
               chat_room = new Chat_room(ui->User_line->text(),nullptr);
               connect(chat_room,&Widget::destroyed,this,[this](){
                   chat_room =nullptr;
               });}
               else{
                   qDebug()<<"showing exisiting register window";
               }
               chat_room->show(); //显示窗口
               chat_room->raise(); //把窗口移到前面
               chat_room->activateWindow();  //激活窗口以便能接受输入
               this->close();
           }
        else {
           QMessageBox::warning(this, "登录", "登录失败，请检查用户名或密码");
       }
}
