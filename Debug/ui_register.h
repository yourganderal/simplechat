/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *new_User_line;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *new_Code_line;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *register_Confirm_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *register_Cancel_btn;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(400, 300);
        label = new QLabel(Register);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 30, 101, 31));
        label->setAlignment(Qt::AlignCenter);
        widget = new QWidget(Register);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(100, 80, 221, 91));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        new_User_line = new QLineEdit(widget);
        new_User_line->setObjectName(QString::fromUtf8("new_User_line"));

        horizontalLayout->addWidget(new_User_line);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        new_Code_line = new QLineEdit(widget);
        new_Code_line->setObjectName(QString::fromUtf8("new_Code_line"));

        horizontalLayout_2->addWidget(new_Code_line);


        verticalLayout->addLayout(horizontalLayout_2);

        widget1 = new QWidget(Register);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(80, 200, 241, 41));
        horizontalLayout_3 = new QHBoxLayout(widget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        register_Confirm_btn = new QPushButton(widget1);
        register_Confirm_btn->setObjectName(QString::fromUtf8("register_Confirm_btn"));

        horizontalLayout_3->addWidget(register_Confirm_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        register_Cancel_btn = new QPushButton(widget1);
        register_Cancel_btn->setObjectName(QString::fromUtf8("register_Cancel_btn"));

        horizontalLayout_3->addWidget(register_Cancel_btn);


        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        label->setText(QCoreApplication::translate("Register", "\346\263\250\345\206\214\351\241\265\351\235\242", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "\350\264\246\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Register", "\345\257\206\347\240\201\357\274\232", nullptr));
        register_Confirm_btn->setText(QCoreApplication::translate("Register", "\347\241\256\345\256\232", nullptr));
        register_Cancel_btn->setText(QCoreApplication::translate("Register", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
