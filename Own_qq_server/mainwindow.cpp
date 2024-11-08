#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    handleNewConnection();//处理客户端新的连接
}

MainWindow::~MainWindow()
{
    if (QSqlDatabase::database().isOpen()) {
           QSqlDatabase::database().close();
       }
    delete ui;
}
//连接客户端，处理连接
void MainWindow::handleNewConnection(){
    mServer = new QTcpServer;
    bool flag=mServer->listen(QHostAddress::Any,6666);
    if(flag){
        //监听成功
        QMessageBox::information(this,"监听状态","监听成功");
        //当有客户端成功连接到服务器 会触发信号
        connect(mServer,QTcpServer::newConnection,this,[this](){
            //准备接受并处理消息
            //返回下一个即将连接的套接字
            mSocket = mServer->nextPendingConnection();
            //有新的消息时 触发readyRead信号 准备阅读信号
            if(mSocket){
                //QMessageBox::information(this,"连接状态","连接成功");
                connect(mSocket,QTcpSocket::readyRead,this,&MainWindow::readClientData);
                //启动线程
                myThead *t =new myThead(mSocket); //创建线程对象
                t->start();              //开始线程
            }
        });

    }

}

//用于读取客户端发送的数据进行处理
void MainWindow::readClientData(){
    QTcpSocket *mSocket = qobject_cast<QTcpSocket*>(sender());
    if(!mSocket) return ;

    QByteArray data = mSocket->readAll();
    qDebug() << "Received raw data:" << data;
    QJsonDocument jsondoc=QJsonDocument::fromJson(data);
    if(!jsondoc.isObject()){
        qDebug()<<"Received invalid JSON data";
        return ;
    }
    QJsonObject jsonobject=jsondoc.object();
    //操作方式  0-登录功能  1-注册功能  2-添加好友功能 3-获取当前用户的好友申请  4-同意好友申请  5-拒绝好友请求
    // 6-获取当前用户的好友  7-用户发送消息
    int way=jsonobject["way"].toInt();
    qDebug()<<"收到的 jsondata"<<QString(data);
     qDebug()<<"way="<<way;

    if(way==1 ||way==0){
    //服务器连上数据库1 账号密码数据库
    ConnectDatebase1();
    QString username= jsonobject["username"].toString();
    QString usercode= jsonobject["usercode"].toString();

//    qDebug()<<"username:"<<username;
//    qDebug()<<"usercode:"<<usercode;
//    qDebug()<<"way:"<<way;
    if(way==0){
    //进行数据库验证
    int isVaild = checkUserCredentials(username,usercode);
    //发送响应给客户端
    QJsonObject responseobject;
    responseobject["status"]=isVaild?"success":"failure";
    QJsonDocument responsedoc(responseobject);
    mSocket->write(responsedoc.toJson());
    mSocket->flush();
    qDebug()<<"服务端发送数据："<<mSocket;}
    if(way==1){
        //到数据库中添加数据
        int isregister =checkisregister(username,usercode);
        //发送到客户端
        QJsonObject responseobject;
        //responseobject["status"]=isregister?"success":"failure";
        if(isregister==0){
            responseobject["status"]="failure";
        }
        if(isregister==1){
            responseobject["status"]="success";
        }
        if(isregister==2){
            responseobject["status"]="exist";
        }
        QJsonDocument responsedoc(responseobject);
        mSocket->write(responsedoc.toJson());
        mSocket->flush();
        qDebug()<<"服务器发送数据："<<mSocket;
            }
    }
    if(way==2){
        //添加好友功能
        QString usernameA=jsonobject["usernameA"].toString();
        QString usernameB=jsonobject["usernameB"].toString();
        qDebug()<<"usernameA="<<usernameA;
        qDebug()<<"usernameB="<<usernameB;

        if(checkUser_is_exist(usernameB)&& !checkUser_is_sendadd(usernameA,usernameB)){      //如果1存在进行下面的操作
        //连上数据库2 添加好友数据库
        QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");  //设置数据库的主机ip
        db.setPort(3306);  //设置数据库的端口号
        db.setUserName("root");  //用户名
        db.setPassword("124362041");  //Mysql的密码
        //设置数据库的名字
        db.setDatabaseName("friendships");
        //打开数据库
        if(db.open()==false){
            qDebug()<<"NO Open DataBase2 !";
            qDebug()<<db.lastError().text();  //输出错误信息
        }
        else qDebug()<<"Success Open DataBase2 !";


    //进行数据库验证
    bool isVaild = checkaddnewuser(usernameA,usernameB);
    //发送给客户端
    QJsonObject responseobject;
    responseobject["status"]=isVaild?"success":"failure";
    QJsonDocument responsedoc(responseobject);
    mSocket->write(responsedoc.toJson());
    mSocket->flush();
    qDebug()<<"服务端发送数据"<<mSocket;
        }
        else{            //如果数据库1里面没有此用户名，返回cant_find给客户端  如果数据库2有此人但是已经发送过好友请求
            QJsonObject responseobject;
            if(checkUser_is_sendadd(usernameA,usernameB)){
                responseobject["status"]="is_send";
                QJsonDocument responsedoc(responseobject);
                mSocket->write(responsedoc.toJson());
                mSocket->flush();
            }else{
            responseobject["status"]="cant_find";
            QJsonDocument responsedoc(responseobject);
            mSocket->write(responsedoc.toJson());
            mSocket->flush();}
        }
}
    if(way==3){
        //此函数用户A用户获取其他用户的好友申请
        QString usernameA=jsonobject["usernameA"].toString();
        get_newfriends(usernameA);
        qDebug()<<"发送好友申请表成功";
    }
    if(way==4){
        //此函数用于同意好友申请
        QString usernameA=jsonobject["usernameA"].toString();
        QString usernameB=jsonobject["usernameB"].toString();
        accept_friends(usernameA,usernameB);
        qDebug()<<"添加好友成功";
    }
    if(way==5){
        //此函数用于拒绝好友申请
        QString usernameA=jsonobject["usernameA"].toString();
        QString usernameB=jsonobject["usernameB"].toString();
        reject_others(usernameA,usernameB);
        qDebug()<<"拒绝成功";
    }
    if(way==6){
        //此函数获取用户的好友
        qDebug()<<"way==6";
        QString usernameB=jsonobject["usernameB"].toString();
        get_friends(usernameB);
    }
    if(way==7){
        //此函数发送消息从A到B
        qDebug()<<"way==7";
        //解析json数据
        QString usernameA = jsonobject["usernameA"].toString();
        QString usernameB = jsonobject["usernameB"].toString();
        QString text= jsonobject["text"].toString();
//        bool isBold = jsonobject["bold"].toBool();
//        bool isItalic = jsonobject["italic"].toBool();
//        bool isUnderline = jsonobject["underline"].toBool();
//        QColor color = QColor(jsonobject["color"].toString());

        //如果用户离线的话执行下面的函数
        //save_in_message(const QString &usernameA, const QString &usernameB, const QString &text,
        //bool isItalic, bool isUnderline, const QColor &color)
        save_in_message(usernameA,usernameB,text);
    }
    if(way==8){
        //读取B发给A的消息
        //解析json数据
        QString usernameA= jsonobject["usernameA"].toString();
        QString usernameB=jsonobject["usernameB"].toString();
        read_message(usernameA,usernameB);
    }
}
//用于验证用户名和密码是否正确
bool MainWindow::checkUserCredentials(const QString &username, const QString &password)
{
    QSqlQuery query;
    QString qs = QString("select * from user_data where User_name ='%1' and User_code='%2'").arg(username).arg(password);

    if (!query.exec(qs)) {
        qDebug()<<"查询失败"<< query.lastError().text();
        return false;// 验证失败
    }
    else {
            // 检查是否有匹配的记录
            if (query.next()) {
                return true; // 验证成功：找到匹配的记录
            } else {
                qDebug() << "没有找到匹配的记录"; // 输出调试信息
                return false; // 验证失败：没有找到匹配的记录
            }
         }
}
//用于注册用户名和密码是否正确
int MainWindow::checkisregister(const QString &username, const QString &password){
    QSqlQuery query;
    QString qs=QString("select * from user_data where User_name='%1'").arg(username);
    if(!query.exec(qs)){
        qDebug()<<"查询数据库失败"<<query.lastError().text();
        return 0;
    }
    else{
        if(!query.next()){
    QSqlQuery query2;
    QString qs2 =QString("insert into user_data(User_name,User_code) Value('%1','%2')").arg(username).arg(password);
    if(!query2.exec(qs2)){
        qDebug()<<"添加失败"<<query2.lastError().text();
        return 0;  //添加失败
    }
    else{
        //添加记录成功
        return 1;
      }
        } //没有重复的话执行这个
        //有重复的话：
        else{
            return 2;
        }
    }
}
//用于验证加好友是否成功
bool MainWindow::checkaddnewuser(const QString &usernameA,const QString &usernameB){
    //自己加自己是不行的
    if(usernameA==usernameB) return false;
    QSqlQuery query;
    QString qs= QString("insert into friendships(User_A_id,User_B_id,status) Value('%1','%2','%3')")
            .arg(usernameA).arg(usernameB).arg(0);

    if(!query.exec(qs)){
        qDebug()<<"添加失败"<<query.lastError().text();
        return false;
    }
    else{
        return true;
    }
}
//查询用户是否在数据库1中
bool MainWindow::checkUser_is_exist(const QString &username){
    //先上数据库1 看添加的好友是否存在
    ConnectDatebase1();

    //查询操作
    QSqlQuery query;
    QString qs= QString("select * from user_data where User_name='%1'").arg(username);
    if(!query.exec(qs)){
        qDebug()<<"查询失败"<<query.lastError().text();
        return false;
    }
    else{
        // 检查是否有匹配的记录
        if (query.next()) {
            return true; // 验证成功：找到匹配的记录
        } else {
            qDebug() << "没有找到匹配的记录"; // 输出调试信息
            return false; // 验证失败：没有找到匹配的记录
        }
    }
}
//检查是否已经发送过好友请求：
bool MainWindow::checkUser_is_sendadd(const QString &usernameA,const QString &usernameB){
    ConnectDatebase2();
    //查询操作：
    QSqlQuery query;
    QString qs =QString("select * from friendships where User_A_id='%1' and User_B_id='%2'")
            .arg(usernameA).arg(usernameB); //("select * from user_data where User_name='%1'").arg(username);
   if(!query.exec(qs)){
        qDebug()<<"查询失败"<<query.lastError().text();
        return true;
    }
    //else{
        if(query.next()){
            return true;    //查询到结果,就不能申请了
        }else{
            qDebug()<<"没查到";
            return false;   //没查询到结果,可以申请添加好友
        }
   // }
}
//获取向用户A申请好友的用户
void MainWindow::get_newfriends(const QString &usernameA){
    //连上数据库2 添加好友数据库
    ConnectDatebase2();
    //寻找数据库2里面User_B_id=usernameA的用户
    QString userAid;//加好友的人
    QSqlQuery query;   //存放查询到的 User_A_id (单个)
    QJsonArray userAidArray;  //用于存放所有匹配的 User_A_id
    QString qs =QString("select User_A_id from friendships where User_B_id='%1'and status='0'").arg(usernameA);
    if(!query.exec(qs)){
        qDebug()<<"查询失败";
    }
    else{
//        if(query.next()){
//            userAid=query.value("User_A_id").toString();
//            qDebug()<<"Use_A_id="<<userAid;
//        }else{
//            qDebug()<<"空";
//        }

        while(query.next()){
            userAid = query.value("User_A_id").toString();
            qDebug()<<"User_A_id="<<userAid;
            userAidArray.append(userAid);  //将 User_A_id 添加到数组中
        }
        if(userAid.isEmpty()){
            qDebug()<<"查询为空";
        }
    }
//顺便将查询到的userAid传给客户端
    QJsonObject responseobject;
    responseobject["userAid"]=userAidArray;
    QJsonDocument responsedoc(responseobject);
    QByteArray jsonData = responsedoc.toJson();
    qDebug() << "JSON Data to be sent:" << jsonData;
    mSocket->write(jsonData);
    mSocket->flush();
}

//拒绝好友申请
void MainWindow::reject_others(const QString &usernameA, const QString &usernameB){
    //连上数据库2 添加好友数据库
    ConnectDatebase2();
    QSqlQuery query;
    //构建 sql updata语句
    QString qs = QString("update friendships set status=2 where User_A_id='%1' and User_B_id='%2'")
            .arg(usernameA).arg(usernameB);
    if (query.exec(qs)) {
        qDebug() << "成功更新状态";
    } else {
        qDebug() << "更新状态失败：" << query.lastError().text();
    }
}
//接受好友申请  //updata 数据库friendship 添加到聊天记录数据库
void MainWindow::accept_friends(const QString &usernameA, const QString &usernameB){
    //连上数据库2 添加好友数据库
    ConnectDatebase2();
    QSqlQuery query;
    //构建 sql updata语句
    QString qs = QString("update friendships set status=1 where User_A_id='%1' and User_B_id='%2'")
            .arg(usernameA).arg(usernameB);
    QString qs2= QString("insert into friendships(User_B_id,User_A_id,status) Value('%1','%2','%3')")
            .arg(usernameA).arg(usernameB).arg(1);

    if(!query.exec(qs2)){
        qDebug()<<"添加失败"<<query.lastError().text();
    }
    if (query.exec(qs)) {
        qDebug() << "成功更新状态";
        //下面是添加联系人到聊天记录的函数
        //get_friends_tochat(usernameA,usernameB);
    } else {
        qDebug() << "更新状态失败：" << query.lastError().text();
    }
}
//获取B的好友
void MainWindow::get_friends(const QString &usernameB){
    ConnectDatebase2();
    //查询User_B_id=usernameB 且 status=1 的User_A_id的值
    QSqlQuery query;  //查询到的朋友(单个)
    QJsonArray userAidArray; //用于存放B的所有好友
    QString userAid;  //好友
    QString qs=QString("select User_A_id from friendships where User_B_id='%1' and status='1'").arg(usernameB);
    if(!query.exec(qs)){
        qDebug()<<"查询好友失败";
    }
    else{
        while(query.next()){
            userAid=query.value("User_A_id").toString();
            qDebug()<<"User_A_id: "<<userAid;
            userAidArray.append(userAid);
        }
    }
    //把查询到的userAid传给客户端
    QJsonObject responseobject;
    responseobject["userAid"]=userAidArray;
    QJsonDocument responsedoc(responseobject);
    QByteArray jsonData = responsedoc.toJson();
    qDebug()<<"jsondata 发送:"<<jsonData;
    mSocket->write(jsonData);
    mSocket->flush();
}
//把A和B放入user_message数据库中   //没必要
void MainWindow::get_friends_tochat(const QString &usernameA, const QString &usernameB){
    ConnectDatebase3();
    QSqlQuery query;
    QString qs= QString("insert into user_message(send_username,receive_username) Value('%1','%2')")
            .arg(usernameA).arg(usernameB);
    QString qs2=QString("insert into user_message(send_username,receive_username) Value('%1','%2')")
            .arg(usernameB).arg(usernameA);
    if(!query.exec(qs2)||!query.exec(qs)){
        qDebug()<<"添加失败"<<query.lastError().text();
    }
}
//3
void MainWindow::save_in_message(const QString &usernameA, const QString &usernameB, const QString &text){
    //打开数据库3
    ConnectDatebase3();
    QSqlQuery query;
    QString qs =QString("insert into user_message(send_username,receive_username,text) Value('%1','%2','%3')")
            .arg(usernameA).arg(usernameB).arg(text);
    if(!query.exec(qs)){
        qDebug()<<"添加失败"<<query.lastError().text();
    }
}
//3
void MainWindow::read_message(const QString &usernameA, const QString &usernameB){
    //打开数据库3
    ConnectDatebase3();
    QSqlQuery query; //查询到的聊天记录
    QString qs = QString("select send_username, receive_username, text from user_message where (send_username='%1' AND receive_username='%2') or (send_username='%2' and receive_username='%1')")
                       .arg(usernameA, usernameB);
    if(!query.exec(qs)){
        qDebug()<<"查询失败"<<query.lastError().text();
        return ;
    }
    //创建一个json数组来存储消息
    QJsonArray messageArray;
    //遍历查询结果
    while(query.next()){
        QJsonObject messageObject;
        messageObject["send_username"]=query.value("send_username").toString();
        messageObject["receive_username"] = query.value("receive_username").toString();
        messageObject["text"] = query.value("text").toString();
//        messageObject["bold"] = query.value("bold").toBool();
//        messageObject["italic"] = query.value("italic").toBool();
//        messageObject["under_line"] = query.value("under_line").toBool();
//        messageObject["color"] = query.value("color").toString();
        //将消息对象添加到json数组中
        messageArray.append(messageObject);
    }
    //将json数据转换为json文档
    QJsonDocument jsonDocument(messageArray);
    //将json文档转换为字符串
    QByteArray jsonData =jsonDocument.toJson();
    qDebug()<<"jsonData发送："<<jsonData;
    mSocket->write(jsonData);
    mSocket->flush();
}
//连接数据库1
void MainWindow::ConnectDatebase1(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");  //设置数据库的主机ip
    db.setPort(3306);  //设置数据库的端口号
    db.setUserName("root");  //用户名
    db.setPassword("124362041");  //Mysql的密码
    //设置数据库的名字
    db.setDatabaseName("userdata");
    //打开数据库
    if(db.open()==false){
        qDebug()<<"NO Open DataBase1 !";
        qDebug()<<db.lastError().text();  //输出错误信息
    }
    else qDebug()<<"Success Open DataBase1 !";
}
//连接数据库2
void MainWindow::ConnectDatebase2(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");  //设置数据库的主机ip
    db.setPort(3306);  //设置数据库的端口号
    db.setUserName("root");  //用户名
    db.setPassword("124362041");  //Mysql的密码
    //设置数据库的名字
    db.setDatabaseName("friendships");
    //打开数据库
    if(db.open()==false){
        qDebug()<<"NO Open DataBase2 !";
        qDebug()<<db.lastError().text();  //输出错误信息
    }
    else qDebug()<<"Success Open DataBase2 !";
}
//连接数据库3
void MainWindow::ConnectDatebase3(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");  //设置数据库的主机ip
    db.setPort(3306);  //设置数据库的端口号
    db.setUserName("root");  //用户名
    db.setPassword("124362041");  //Mysql的密码
    //设置数据库的名字
    db.setDatabaseName("user_message");
    //打开数据库
    if(db.open()==false){
        qDebug()<<"NO Open DataBase3 !";
        qDebug()<<db.lastError().text();  //输出错误信息
    }
    else qDebug()<<"Success Open DataBase3 !";
}
