/********************************************************************************
** Form generated from reading UI file 'add_new_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_NEW_WIDGET_H
#define UI_ADD_NEW_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_new_widget
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *add_username;
    QSplitter *splitter;
    QPushButton *add_btn;
    QPushButton *cancel_btn;
    QPushButton *new_friends;
    QLabel *label_3;

    void setupUi(QWidget *Add_new_widget)
    {
        if (Add_new_widget->objectName().isEmpty())
            Add_new_widget->setObjectName(QString::fromUtf8("Add_new_widget"));
        Add_new_widget->resize(671, 224);
        label = new QLabel(Add_new_widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 20, 91, 21));
        label->setBaseSize(QSize(2, 2));
        label->setTabletTracking(false);
        label->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(Add_new_widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(72, 62, 471, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        add_username = new QLineEdit(layoutWidget);
        add_username->setObjectName(QString::fromUtf8("add_username"));

        horizontalLayout->addWidget(add_username);

        splitter = new QSplitter(Add_new_widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(170, 130, 271, 21));
        splitter->setOrientation(Qt::Horizontal);
        add_btn = new QPushButton(splitter);
        add_btn->setObjectName(QString::fromUtf8("add_btn"));
        splitter->addWidget(add_btn);
        cancel_btn = new QPushButton(splitter);
        cancel_btn->setObjectName(QString::fromUtf8("cancel_btn"));
        splitter->addWidget(cancel_btn);
        new_friends = new QPushButton(Add_new_widget);
        new_friends->setObjectName(QString::fromUtf8("new_friends"));
        new_friends->setGeometry(QRect(560, 160, 51, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/C:/Users/30797/Desktop/icons_/new_friend.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        new_friends->setIcon(icon);
        new_friends->setIconSize(QSize(30, 30));
        label_3 = new QLabel(Add_new_widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 180, 60, 16));

        retranslateUi(Add_new_widget);

        QMetaObject::connectSlotsByName(Add_new_widget);
    } // setupUi

    void retranslateUi(QWidget *Add_new_widget)
    {
        Add_new_widget->setWindowTitle(QCoreApplication::translate("Add_new_widget", "Form", nullptr));
        label->setText(QCoreApplication::translate("Add_new_widget", "\346\267\273\345\212\240\350\201\224\347\263\273\344\272\272", nullptr));
        label_2->setText(QCoreApplication::translate("Add_new_widget", "\350\246\201\346\267\273\345\212\240\347\232\204\350\264\246\345\217\267\357\274\232", nullptr));
        add_btn->setText(QCoreApplication::translate("Add_new_widget", "\346\267\273\345\212\240", nullptr));
        cancel_btn->setText(QCoreApplication::translate("Add_new_widget", "\345\217\226\346\266\210", nullptr));
        new_friends->setText(QString());
        label_3->setText(QCoreApplication::translate("Add_new_widget", "\346\226\260\347\232\204\346\234\213\345\217\213\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add_new_widget: public Ui_Add_new_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_NEW_WIDGET_H
