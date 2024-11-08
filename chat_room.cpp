#include "chat_room.h"
#include "ui_chat_room.h"

Chat_room::Chat_room(QString username,QWidget *parent) :
    QWidget(parent),m_username(username),
    ui(new Ui::Chat_room)
{
    ui->setupUi(this);
    qDebug()<<"username: "<<m_username;
    ui->label_User->setText(m_username);
    //连接一下服务器
    mSocket = new QTcpSocket;
    QString ip="192.168.31.135";
    mSocket->connectToHost(QHostAddress(ip),6666);//连接到主机
    if(mSocket->waitForConnected()){
        qDebug()<<"好友申请表已连接到服务器";
    }else{
        QMessageBox::warning(this,"警告","连接超时");
    }
    //连接信号和槽
    connect(ui->Chat_list,&QListWidget::itemClicked,this,&Chat_room::onItemClicked);
    ui->send_btn->setEnabled(false);
    initFontSizeBox();//初始化字体大小
    initFontComboBox();//初始化字体
}

Chat_room::~Chat_room()
{
    delete ui;
}

void Chat_room::on_add_new_btn_clicked()  //添加联系人
{
    //当添加联系人按钮被点击时 ,先检查添加联系人窗口是否存在
    if(add_new_window==nullptr){
        add_new_window = new Add_new_widget(m_username,nullptr);  //如果没有，新建一个窗口
        connect(add_new_window,&QWidget::destroyed,this,[this]{
            add_new_window=nullptr; //清理指针
        });
    }else{
        qDebug()<<"添加联系人窗口已存在";
    }
    add_new_window->show();
    add_new_window->raise();
    add_new_window->activateWindow(); //激活窗口以便输入
}
//获取用户好友
void Chat_room::get_friendname(const QString usernameB){
    //获取当前用户的好友功能
    int way=6;
    QString username_B=usernameB;
    //构建json串
    QJsonObject jsonbject;
    jsonbject["usernameB"]=username_B;
    jsonbject["way"]=way;
    //将jsondata转换成字符串
    QJsonDocument jsondoc(jsonbject);
    QByteArray jsonData = jsondoc.toJson();
    qDebug()<<"way ="<<way;
    qDebug()<<"获取该用户的好友："<<jsonData;
    //将json数据传到服务器
    if(mSocket && mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();
    }else{
        qDebug()<<"服务器连接失败;";
    }
    slot_read();

}
//读取服务端的数据
void Chat_room::slot_read(){
    //确保有数据可读
    if(mSocket->bytesAvailable()==0){
        qDebug()<<"没有读到数据";
        return;
    }
    //接受服务端发来的json数据
    QByteArray data =mSocket->readAll();
    qDebug()<<"从服务端读来的数据："<<data;
    //解析json数据
    QJsonDocument jsondoc =QJsonDocument::fromJson(data);
    if(!jsondoc.isObject()){
        qDebug()<<"收到不合法的json数据";
        return;
    }

    QJsonObject jsonObject = jsondoc.object();
    //检查"userAid"字段是否存在并且是数组
    if(jsonObject.contains("userAid")&&jsonObject["userAid"].isArray()){
        QJsonArray QJsonArray = jsonObject["userAid"].toArray();
        //遍历数组并处理每个userAid
        for(const QJsonValue &value :QJsonArray){
            if(value.isString()){
                QString new_friend_data =value.toString();
                qDebug()<<"new friends data:"<<new_friend_data;
                addFriendItem(new_friend_data);   //把得到的数据传给QListWidget
            }
        }
    }

}
//把好友展示在listwidget中
void Chat_room::addFriendItem(const QString &userAid){
    auto* itemWidget = new QWidget(ui->Chat_list);
    auto* layout =new QHBoxLayout(itemWidget);
    //创建 QLabel 并设置文本
    auto* label =new QLabel(userAid,itemWidget);
    //设置字体大小
    QFont font = label->font();
    font.setPointSize(14);//设置字体大小
    label->setFont(font);
    layout->addWidget(label);
    layout->setAlignment(Qt::AlignCenter);//居中
    layout->setContentsMargins(0,0,0,0);
    itemWidget->setLayout(layout);

    QListWidgetItem* listltem = new QListWidgetItem(ui->Chat_list);
    //设置 QListWidgetItem 的高度
    listltem->setSizeHint(QSize(0,100));  //设置项的高度为50px
    ui->Chat_list->setItemWidget(listltem,itemWidget);
}
//更新按钮
void Chat_room::on_renew_Btn_clicked()
{
    //刷新
    ui->Chat_list->clear();
    //获取好友的名字  并展示在chat_list上
    get_friendname(m_username);


}
//点击listwidget中的好友
void Chat_room::onItemClicked(QListWidgetItem* item){
    //获取被点击的widget

    QWidget* widget = ui->Chat_list->itemWidget(item);
    QLabel* label=widget->findChild<QLabel*>();
    QString your_friend=label->text();
    if(label){
        ui->chose_friend->setText(your_friend);
        //接下来调用处理函数  //激活send_btn按钮
        ui->send_btn->setEnabled(true);
    }
    //再获取与该用户的聊天内容 read_message(自己,对方);
    ui->textBrowser->clear();
    read_message_slot(m_username,your_friend);
    ui->textBrowser->repaint();
}

void Chat_room::on_send_btn_clicked()
{
    qDebug()<<"发送按钮被点击";
    QString your_friend=ui->chose_friend->text();
    //发送msg_text里面的文本内容
    sendStyleText();

}
//发送带样式的文本
void Chat_room::sendStyleText(){ //3
    int way=7;
    QTextDocument *document = ui->msg_text->document();
    QString text = document->toPlainText();//获取纯文本内容
//    QTextCursor cursor = ui->msg_text->textCursor();
//    QTextCharFormat charFormat = cursor.charFormat();
    //获取文本样式
//    QFont font = charFormat.font();
//    bool isBold =font.bold();
//    bool isItalic = font.italic();
//    bool isUnderline =font.underline();
//    QColor color = charFormat.foreground().color();
    //构建json对象
    QJsonObject jsonObject;
    jsonObject["text"]=text;
    jsonObject["way"]=way;
//    jsonObject["bold"]=isBold;
//    jsonObject["italic"]=isItalic;
//    jsonObject["underline"]=isUnderline;
//    jsonObject["color"]=color.name();
    jsonObject["usernameA"]=ui->label_User->text();
    jsonObject["usernameB"]=ui->chose_friend->text();
    //将json对象转为字符串
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData =jsonDoc.toJson();
    //发送数据到服务器
    if(mSocket && mSocket->state() == QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();
    }else{
        qDebug()<<"服务器连接失败";
    }
}

//初始化字体大小
void Chat_room::initFontSizeBox(){
    //添加常见的字体大小 到QComboBox
    QList<int> fontSizes={8,10,12,14,16,18,20,24,26};
    for(int size:fontSizes){
        ui->size_Box->addItem(QString::number(size),size);  //使用数据角色存储字体大小
    }
    //连接信号和槽
    connect(ui->size_Box,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,
            &Chat_room::on_size_Box_currentIndexChanged);
}
//初始化字体
void Chat_room::initFontComboBox(){
    //获取系统支持的字体
    QFontDatabase fontDB;
    QStringList fonts = fontDB.families();
    //添加字体到 Combox
    for(const QString &font :fonts){
        ui->comboBox->addItem(font);
    }
}
void Chat_room::on_size_Box_currentIndexChanged(int FontSize)
{
    if(FontSize>=0){
        int fontsize=ui->size_Box->itemData(FontSize).toInt(); //获取当前大小
        QTextCharFormat fmt;
        fmt.setFontPointSize(fontsize);
        ui->msg_text->mergeCurrentCharFormat(fmt);  //更新文本编辑器的字体大小
    }

}

void Chat_room::on_comboBox_currentIndexChanged(const QString &fontFamily)  //改变字体
{
    QTextCharFormat fmt;
    fmt.setFontFamily(fontFamily);
    ui->msg_text->mergeCurrentCharFormat(fmt);
}
//加粗
void Chat_room::on_Size_Btn_clicked(bool checked)
{
    if(checked) ui->msg_text->setFontWeight(QFont::Bold);
    else{
        ui->msg_text->setFontWeight(QFont::Normal);
    }
    ui->msg_text->setFocus();
}
//斜体
void Chat_room::on_I_Btn_clicked(bool checked)
{
    ui->msg_text->setFontItalic(checked);
    ui->msg_text->setFocus();
}
//下划线
void Chat_room::on_under_line_Btn_clicked(bool checked)
{
    ui->msg_text->setFontUnderline(checked);
    ui->msg_text->setFocus();
}
//颜色
void Chat_room::on_Color_Btn_clicked()
{
    QColor color;
    color=QColorDialog::getColor(color,this);
    if(color.isValid()){
        ui->msg_text->setTextColor(color);
        ui->msg_text->setFocus();
    }
}
//读取B发给A的消息
void Chat_room::read_message_slot(const QString &usernameA, const QString &usernameB){
    qDebug()<<"执行way=8读取聊天记录";
    //发送个way=8表示读取用户B给A的聊天记录
    int way=8;
    //构建json串
    QJsonObject jsonobject;
    jsonobject["usernameA"]=usernameA;
    jsonobject["usernameB"]=usernameB;
    jsonobject["way"]=way;
    //将json转化成字符串
    QJsonDocument jsondoc(jsonobject);
    QByteArray jsonData = jsondoc.toJson();
    //发送json数据到服务器
    if(mSocket && mSocket->state()==QAbstractSocket::ConnectedState){
        mSocket->write(jsonData);
        mSocket->flush();
    }else{
        qDebug()<<"服务器连接失败";
    }
    read_message();

}
void Chat_room::read_message(){
    //读取服务器发来的数据
    if(mSocket->bytesAvailable()==0){
        qDebug()<<"没有收到数据";
        //retrun;
    }
    //接收到服务器发过来的json数据
    QByteArray data =mSocket->readAll();
    qDebug()<<"8888收到的data:"<<data;
    //解析json数据
    QJsonDocument jsonDoc =QJsonDocument::fromJson(data);
    if(!jsonDoc.isNull()){
        if(jsonDoc.isArray()){
            QJsonArray jsonArray = jsonDoc.array();
            for(const QJsonValue &value :jsonArray){
                if(value.isObject()){
                    QJsonObject jsonObject = value.toObject();
                    QString sendUsername = jsonObject["send_username"].toString();
                    QString receiveUsername = jsonObject["receive_username"].toString();
                    QString text = jsonObject["text"].toString();
                    qDebug() << "用户：" << sendUsername << "发给" << receiveUsername << ":  " << text;
                    // 格式化消息
                    QString formattedMessage = QString("用户: %1 : %2\n")
                            .arg(sendUsername).arg(text);
                    //在QTextBrowser 中显示消息

                    ui->textBrowser->append(formattedMessage);
                }
            }
        }else{
            qDebug()<<"Failed to parse JSON data";
        }
    }else{
        qDebug()<<"连接失败";
    }

}
