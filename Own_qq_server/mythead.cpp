#include "mythead.h"

myThead::myThead(QTcpSocket *s)
{
    socket=s;
}

void myThead::run(){
    if(socket){
        //连接信号和槽
    connect(socket,&QTcpSocket::readyRead,this,&myThead::clientInfoSlot);
    //进入事件循环，等待信号和槽的触发
    exec();
    }
}

void myThead::clientInfoSlot(){
    if(socket){
        QByteArray data = socket->readAll();
        //处理接收到的数据
        qDebug()<<"服务端收到："<<data;
    }
}
