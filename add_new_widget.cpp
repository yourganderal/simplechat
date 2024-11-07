#include "add_new_widget.h"
#include "ui_add_new_widget.h"

Add_new_widget::Add_new_widget(QString username_A,QWidget *parent) :
    QWidget(parent),myusername(username_A),
    ui(new Ui::Add_new_widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket;
    QString ip="192.168.31.135";
    mSocket->connectToHost(QHostAddress(ip),6666); //连接到主机
    if(mSocket->waitForConnected()){
        qDebug()<<"添加用户界面已经连接到服务端";
    }else{
        QMessageBox::warning(this,"警告","连接超时");
    }
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(slot_read()));
}

Add_new_widget::~Add_new_widget()
{
    delete ui;
}

void Add_new_widget::on_add_btn_clicked()
{
    qDebug()<<"添加按钮被点击";
    int way=2; //操作方式为2-添加好友
    QString usernameB=ui->add_username->text();
    QString usernameA=myusername;
    qDebug()<<"usernameA="<<usernameA;
    qDebug()<<"usernameB="<<usernameB;
    //构建json串
    QJsonObject jsonobject;
    jsonobject["usernameA"]=usernameA;
    jsonobject["usernameB"]=usernameB;
    jsonobject["way"]=way;
    //将json转换成字符串
    QJsonDocument jsondoc(jsonobject);
    QByteArray jsonData = jsondoc.toJson();
    //发送json数据到服务器
    if(mSocket && mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();

        slot_read();
    }else{
        qDebug()<<"Socket is not connect";
    }

}

void Add_new_widget::slot_read(){
    if(mSocket->bytesAvailable()==0){
        qDebug()<<"没有读到数据";
        return;
    }
    //准备读取服务端返回的结果，是否添加联系人成功
    QByteArray data = mSocket->readAll();
    qDebug()<<"Receive data"<< data;
    //解析json数据
    QJsonDocument jsondoc =QJsonDocument::fromJson(data);
    if(!jsondoc.isObject()){
        qDebug()<<"收到不合法的json数据";
        return ;
    }
    QJsonObject jsonObject=jsondoc.object();
    QString status=jsonObject["status"].toString(); //获取响应状态
    //对响应状态进行处理
    if(status=="success"){
        QMessageBox::information(this,"好友申请","申请成功");
    }
    if(status=="cant_find"){
        QMessageBox::warning(this,"警告","查无此人");
    }
    if(status=="failure"){
        QMessageBox::warning(this,"警告","申请失败");
    }
    if(status=="is_send"){
        QMessageBox::warning(this,"警告","已经提交过申请");
    }

}

void Add_new_widget::on_new_friends_clicked()
{
    //此处转跳到有新的好友申请界面
    if(new_friend_window==nullptr){
        new_friend_window=new New_friend(myusername,nullptr);
        connect(new_friend_window,&QWidget::destroyed,this,[this]{
            new_friend_window=nullptr;  //清理指针
        });
    }else{
        qDebug()<<"添加新好友窗口已经存在。";
    }
    new_friend_window->show();
    new_friend_window->raise();
    new_friend_window->activateWindow();
}
