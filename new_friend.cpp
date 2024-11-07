#include "new_friend.h"
#include "ui_new_friend.h"

New_friend::New_friend(QString usernameA,QWidget *parent) :
    QWidget(parent),m_usernameA(usernameA),
    ui(new Ui::New_friend)
{
    ui->setupUi(this);
    ui->UserA_label->setText(m_usernameA);
    mSocket = new QTcpSocket;
    QString ip="192.168.31.135";
    mSocket->connectToHost(QHostAddress(ip),6666);//连接到主机
    if(mSocket->waitForConnected()){
        qDebug()<<"好友申请表已连接到服务器";
    }else{
        QMessageBox::warning(this,"警告","连接超时");
    }
    connect(mSocket,&QTcpSocket::connected,this,&New_friend::slot_send);
    connect(mSocket, &QTcpSocket::readyRead, this, &New_friend::slot_read); //依赖信号和槽机制调用来自动读取数据

}

New_friend::~New_friend()
{
    delete ui;
}

void New_friend::slot_read(){
    //确保有数据可读
    if(mSocket->bytesAvailable()==0){
        qDebug()<<"没有收到数据";
        return ;
    }
    //接受服务端发送过来的json数据
    QByteArray data =mSocket->readAll();
    qDebug()<<"Received data:" << data;
    //解析json数据
    QJsonDocument jsondoc =QJsonDocument::fromJson(data);
    if(!jsondoc.isObject()){
        qDebug()<<"收到不合法的json数据";
        return;
    }
    QJsonObject jsonObject =jsondoc.object();
    //检查 "userAid"字段是否存在并且是数组
    //QString new_friends_data=jsonObject["userAid"].toString();
    if(jsonObject.contains("userAid")&& jsonObject["userAid"].isArray()){
        QJsonArray jsonArray = jsonObject["userAid"].toArray();
        //遍历数组并处理每个userAid
        for(const QJsonValue &value :jsonArray){
            if(value.isString()){
                QString new_friend_data = value.toString();
                qDebug()<<"new_friends_data:"<< new_friend_data;
                addFriendItem(new_friend_data);
            }
        }
    }
    //qDebug()<<"new_friends_data: "<<new_friends_data;

}

void New_friend::on_renew_btn_clicked()
{
    //清空列表中的内容
    ui->new_f_list->clear();
    slot_send();
    slot_read();
}
void New_friend::slot_send(){
    //发送way=3的信号给服务端表示请求得到new_friends的申请
    int way=3;
    QString username_A=m_usernameA;
    //构建json串
    QJsonObject jsonobject;
    jsonobject["usernameA"]=username_A;
    jsonobject["way"]=way;
    qDebug()<<"way="<<way;
    //将json转换成字符串
    QJsonDocument jsondoc(jsonobject);
    QByteArray jsonData = jsondoc.toJson();
    //发送json数据到服务器
    if(mSocket && mSocket->state()==QAbstractSocket::ConnectedState){
        qDebug()<<"发送的json data:"<<QString(jsonData);
        mSocket->write(jsonData);
        mSocket->flush();
        //slot_read();
    }else{
        qDebug()<<"服务器连接失败";
    }
}
void New_friend::addFriendItem(const QString &userAid){
    auto* itemWidget = new QWidget(ui->new_f_list);
    auto* layout = new QHBoxLayout(itemWidget);
    auto* label = new QLabel(userAid,itemWidget);
    auto* acceptBtn = new QPushButton("接受",itemWidget);
    auto* rejectBtn = new QPushButton("拒绝",itemWidget);

    layout->addWidget(label);
    layout->addWidget(acceptBtn);
    layout->addWidget(rejectBtn);
    layout->setContentsMargins(0,0,0,0);
    itemWidget->setLayout(layout);

    QListWidgetItem* listItem = new QListWidgetItem(ui->new_f_list);
    ui->new_f_list->setItemWidget(listItem,itemWidget);

    connect(acceptBtn,&QPushButton::clicked,this,[this,userAid](){
        accept_friend(userAid);
    });
    connect(rejectBtn,&QPushButton::clicked,this,[this,userAid](){
        reject_other(userAid);
    });

}
//接受好友申请
void New_friend::accept_friend(const QString &userAid){
    qDebug()<<"接受好友请求按钮被点击";
    //接下来改变好友状态
    int way=4;
    QString usernameA=userAid;
    QString usernameB=m_usernameA;
    //构建json串
    QJsonObject jsonobject;
    jsonobject["usernameA"]=usernameA;
    jsonobject["usernameB"]=usernameB;
    jsonobject["way"]=way;
    //将json转换成字符串
    QJsonDocument jsondoc(jsonobject);
    QByteArray jsonData = jsondoc.toJson();
    qDebug()<<"way = "<<way;
    qDebug()<<"接受好友发送给服务端的jsondata"<<jsonData;
    //发送json数据到服务器
    if(mSocket &&mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();
    }else{
        qDebug()<<"服务器连接失败";
    }
    //刷新一下
    ui->new_f_list->clear();
    slot_send();
    slot_read();
}
//拒绝其他人的申请
void New_friend::reject_other(const QString &userAid){
    qDebug()<<"拒绝好友请求";
    //改变好友状态
    int way=5;
    QString usernameA=userAid;
    QString usernameB=m_usernameA;
    //构建json串
    QJsonObject jsonobject;
    jsonobject["usernameA"]=usernameA;
    jsonobject["usernameB"]=usernameB;
    jsonobject["way"]=way;
    //将json转换成字符串
    QJsonDocument jsondoc(jsonobject);
    QByteArray jsonData = jsondoc.toJson();
    qDebug()<<"way = "<<way;
    qDebug()<<"拒绝好友发送给服务端的jsondata"<<jsonData;
    //发送json数据到服务器
    if(mSocket &&mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();
    }else{
        qDebug()<<"服务器连接失败";
    }
    //刷新一下
    ui->new_f_list->clear();
    slot_send();
    slot_read();
}
