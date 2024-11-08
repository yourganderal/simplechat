#include "register.h"
#include "ui_register.h"
#include <QSqlQuery>  //操作数据库


Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    mSocket= new QTcpSocket;
    //连接服务器
    QString ip ="192.168.31.135";
    mSocket->connectToHost(QHostAddress(ip),6666); //连上主机
    if(mSocket->waitForConnected()){
        qDebug()<<"注册界面连接成功";
    }else{
        qDebug()<<"注册界面连接失败";
    }
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(slot_read()));

}

Register::~Register()
{
    delete ui;
}

void Register::on_register_Cancel_btn_clicked()
{
    this->close();
}

void Register::slot_read(){
    //确保有数据可读
    if(mSocket->bytesAvailable()==0){
        qDebug()<<"没有读到数据";
        return ;
    }
    //实现此函数
    QByteArray data = mSocket->readAll();
    qDebug()<<"Receive data:"<<data;
    //解析 JSON 数据
    QJsonDocument jsondoc =QJsonDocument::fromJson(data);
    if(!jsondoc.isObject()){
        qDebug()<<"接收到不合法的 JSON data";
        return ;
    }
    QJsonObject jsonObject= jsondoc.object();
    QString status= jsonObject["status"].toString(); //获取响应状态
    //根据响应状态进行处理
    if(status=="success"){
        QMessageBox::information(this,"注册状态","注册成功");
    }
    if(status=="failure"){
        QMessageBox::warning(this,"警告","注册失败");
    }
    if(status=="exist"){
        QMessageBox::warning(this,"警告","该用户名已存在");
    }

}

void Register::on_register_Confirm_btn_clicked()
{
    if(ui->new_User_line==nullptr||ui->new_Code_line==nullptr){
        QMessageBox::warning(this,"警告","请输入用户名或密码完整");
    }
    //获取用户输入的数据
    int way=1;   //表示注册方式
    QString Username =ui->new_User_line->text();
    QString Usercode =ui->new_Code_line->text();
    //构建json 串
    QJsonObject jsonobject;
    jsonobject["username"]=Username;
    jsonobject["usercode"]=Usercode;
    jsonobject["way"]=way;
    //将 json 对象转为字符串
    QJsonDocument jsodoc(jsonobject);
    QByteArray jsonData = jsodoc.toJson();
    //将json字符串 数据发送到服务器
    qDebug()<<mSocket;
    if(mSocket && mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();

        //调用接受服务端的函数
        slot_read();
    }else{
        qDebug()<<"Socket连接超时...";
    }
}
