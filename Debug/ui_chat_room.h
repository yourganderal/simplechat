/********************************************************************************
** Form generated from reading UI file 'chat_room.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_ROOM_H
#define UI_CHAT_ROOM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat_room
{
public:
    QLabel *label;
    QLabel *label_User;
    QFrame *line;
    QListWidget *Chat_list;
    QSplitter *splitter;
    QPushButton *add_new_btn;
    QPushButton *User_net_btn;
    QPushButton *renew_Btn;
    QPushButton *pushButton_4;
    QTextBrowser *textBrowser;
    QLabel *chose_friend;
    QTextEdit *msg_text;
    QPushButton *send_btn;
    QSplitter *splitter_2;
    QPushButton *Size_Btn;
    QPushButton *I_Btn;
    QPushButton *under_line_Btn;
    QPushButton *Color_Btn;
    QPushButton *save_Btn;
    QPushButton *clear_Btn;
    QSplitter *splitter_3;
    QLabel *label_2;
    QComboBox *size_Box;
    QSplitter *splitter_4;
    QLabel *label_3;
    QComboBox *comboBox;

    void setupUi(QWidget *Chat_room)
    {
        if (Chat_room->objectName().isEmpty())
            Chat_room->setObjectName(QString::fromUtf8("Chat_room"));
        Chat_room->resize(971, 624);
        label = new QLabel(Chat_room);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 54, 12));
        label_User = new QLabel(Chat_room);
        label_User->setObjectName(QString::fromUtf8("label_User"));
        label_User->setGeometry(QRect(70, 10, 54, 12));
        line = new QFrame(Chat_room);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(53, 50, 20, 551));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        Chat_list = new QListWidget(Chat_room);
        Chat_list->setObjectName(QString::fromUtf8("Chat_list"));
        Chat_list->setGeometry(QRect(60, 50, 121, 631));
        splitter = new QSplitter(Chat_room);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(0, 50, 61, 181));
        splitter->setOrientation(Qt::Vertical);
        add_new_btn = new QPushButton(splitter);
        add_new_btn->setObjectName(QString::fromUtf8("add_new_btn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/add_new_user.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        add_new_btn->setIcon(icon);
        add_new_btn->setIconSize(QSize(30, 30));
        splitter->addWidget(add_new_btn);
        User_net_btn = new QPushButton(splitter);
        User_net_btn->setObjectName(QString::fromUtf8("User_net_btn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/user_net.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        User_net_btn->setIcon(icon1);
        User_net_btn->setIconSize(QSize(30, 30));
        splitter->addWidget(User_net_btn);
        renew_Btn = new QPushButton(splitter);
        renew_Btn->setObjectName(QString::fromUtf8("renew_Btn"));
        splitter->addWidget(renew_Btn);
        pushButton_4 = new QPushButton(splitter);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        splitter->addWidget(pushButton_4);
        textBrowser = new QTextBrowser(Chat_room);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(190, 50, 781, 371));
        chose_friend = new QLabel(Chat_room);
        chose_friend->setObjectName(QString::fromUtf8("chose_friend"));
        chose_friend->setGeometry(QRect(480, 30, 131, 21));
        chose_friend->setAlignment(Qt::AlignCenter);
        msg_text = new QTextEdit(Chat_room);
        msg_text->setObjectName(QString::fromUtf8("msg_text"));
        msg_text->setGeometry(QRect(190, 470, 781, 121));
        send_btn = new QPushButton(Chat_room);
        send_btn->setObjectName(QString::fromUtf8("send_btn"));
        send_btn->setGeometry(QRect(850, 590, 121, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/send.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        send_btn->setIcon(icon2);
        send_btn->setIconSize(QSize(20, 17));
        splitter_2 = new QSplitter(Chat_room);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(570, 430, 391, 31));
        splitter_2->setOrientation(Qt::Horizontal);
        Size_Btn = new QPushButton(splitter_2);
        Size_Btn->setObjectName(QString::fromUtf8("Size_Btn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/bold.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Size_Btn->setIcon(icon3);
        Size_Btn->setIconSize(QSize(24, 24));
        Size_Btn->setCheckable(true);
        splitter_2->addWidget(Size_Btn);
        I_Btn = new QPushButton(splitter_2);
        I_Btn->setObjectName(QString::fromUtf8("I_Btn"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/italic.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        I_Btn->setIcon(icon4);
        I_Btn->setIconSize(QSize(20, 20));
        I_Btn->setCheckable(true);
        splitter_2->addWidget(I_Btn);
        under_line_Btn = new QPushButton(splitter_2);
        under_line_Btn->setObjectName(QString::fromUtf8("under_line_Btn"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/under.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        under_line_Btn->setIcon(icon5);
        under_line_Btn->setIconSize(QSize(30, 30));
        under_line_Btn->setCheckable(true);
        splitter_2->addWidget(under_line_Btn);
        Color_Btn = new QPushButton(splitter_2);
        Color_Btn->setObjectName(QString::fromUtf8("Color_Btn"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/color.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Color_Btn->setIcon(icon6);
        Color_Btn->setIconSize(QSize(40, 40));
        splitter_2->addWidget(Color_Btn);
        save_Btn = new QPushButton(splitter_2);
        save_Btn->setObjectName(QString::fromUtf8("save_Btn"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/save.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        save_Btn->setIcon(icon7);
        save_Btn->setIconSize(QSize(24, 24));
        splitter_2->addWidget(save_Btn);
        clear_Btn = new QPushButton(splitter_2);
        clear_Btn->setObjectName(QString::fromUtf8("clear_Btn"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/clear.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        clear_Btn->setIcon(icon8);
        clear_Btn->setIconSize(QSize(20, 20));
        splitter_2->addWidget(clear_Btn);
        splitter_3 = new QSplitter(Chat_room);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(430, 430, 132, 22));
        splitter_3->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        splitter_3->addWidget(label_2);
        size_Box = new QComboBox(splitter_3);
        size_Box->setObjectName(QString::fromUtf8("size_Box"));
        splitter_3->addWidget(size_Box);
        splitter_4 = new QSplitter(Chat_room);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setGeometry(QRect(190, 430, 231, 22));
        splitter_4->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        splitter_4->addWidget(label_3);
        comboBox = new QComboBox(splitter_4);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        splitter_4->addWidget(comboBox);

        retranslateUi(Chat_room);

        QMetaObject::connectSlotsByName(Chat_room);
    } // setupUi

    void retranslateUi(QWidget *Chat_room)
    {
        Chat_room->setWindowTitle(QCoreApplication::translate("Chat_room", "Form", nullptr));
        label->setText(QCoreApplication::translate("Chat_room", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_User->setText(QCoreApplication::translate("Chat_room", "NULL", nullptr));
        add_new_btn->setText(QString());
        User_net_btn->setText(QString());
        renew_Btn->setText(QCoreApplication::translate("Chat_room", "\345\210\267\346\226\260", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Chat_room", "icon", nullptr));
        chose_friend->setText(QCoreApplication::translate("Chat_room", "\351\200\211\346\213\251\344\270\200\344\270\252\350\201\212\345\244\251\344\272\272", nullptr));
        send_btn->setText(QCoreApplication::translate("Chat_room", "\345\217\221\351\200\201", nullptr));
        Size_Btn->setText(QString());
        I_Btn->setText(QString());
        under_line_Btn->setText(QString());
        Color_Btn->setText(QString());
        save_Btn->setText(QString());
        clear_Btn->setText(QString());
        label_2->setText(QCoreApplication::translate("Chat_room", "\345\244\247\345\260\217\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Chat_room", "\345\255\227\344\275\223\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat_room: public Ui_Chat_room {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_ROOM_H
