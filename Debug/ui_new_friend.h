/********************************************************************************
** Form generated from reading UI file 'new_friend.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_FRIEND_H
#define UI_NEW_FRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_New_friend
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *UserA_label;
    QListWidget *new_f_list;
    QPushButton *renew_btn;

    void setupUi(QWidget *New_friend)
    {
        if (New_friend->objectName().isEmpty())
            New_friend->setObjectName(QString::fromUtf8("New_friend"));
        New_friend->resize(563, 482);
        label = new QLabel(New_friend);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 30, 171, 31));
        label->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(New_friend);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 111, 21));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        UserA_label = new QLabel(layoutWidget);
        UserA_label->setObjectName(QString::fromUtf8("UserA_label"));

        horizontalLayout->addWidget(UserA_label);

        new_f_list = new QListWidget(New_friend);
        new_f_list->setObjectName(QString::fromUtf8("new_f_list"));
        new_f_list->setGeometry(QRect(140, 70, 311, 361));
        renew_btn = new QPushButton(New_friend);
        renew_btn->setObjectName(QString::fromUtf8("renew_btn"));
        renew_btn->setGeometry(QRect(470, 410, 80, 31));

        retranslateUi(New_friend);

        QMetaObject::connectSlotsByName(New_friend);
    } // setupUi

    void retranslateUi(QWidget *New_friend)
    {
        New_friend->setWindowTitle(QCoreApplication::translate("New_friend", "Form", nullptr));
        label->setText(QCoreApplication::translate("New_friend", "\346\226\260\346\234\213\345\217\213\347\224\263\350\257\267", nullptr));
        label_2->setText(QCoreApplication::translate("New_friend", "\350\264\246\345\217\267\357\274\232", nullptr));
        UserA_label->setText(QCoreApplication::translate("New_friend", "NULL", nullptr));
        renew_btn->setText(QCoreApplication::translate("New_friend", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class New_friend: public Ui_New_friend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_FRIEND_H
