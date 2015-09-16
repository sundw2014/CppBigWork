/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLineEdit *user;
    QLineEdit *paw;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(637, 438);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 60, 221, 61));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 150, 221, 61));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 641, 441));
        label->setPixmap(QPixmap(QString::fromUtf8("../file/d8eabccae56f61dc21e236ae766320cd.jpg")));
        user = new QLineEdit(Widget);
        user->setObjectName(QStringLiteral("user"));
        user->setGeometry(QRect(350, 340, 113, 20));
        paw = new QLineEdit(Widget);
        paw->setObjectName(QStringLiteral("paw"));
        paw->setGeometry(QRect(350, 370, 113, 20));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 340, 41, 16));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(300, 370, 31, 16));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(300, 400, 61, 23));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(400, 400, 61, 23));
        label->raise();
        pushButton->raise();
        pushButton_2->raise();
        user->raise();
        paw->raise();
        label_2->raise();
        label_3->raise();
        pushButton_3->raise();
        pushButton_4->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        pushButton->setText(QApplication::translate("Widget", "\345\215\225\344\272\272\345\257\271\346\210\230", 0));
        pushButton_2->setText(QApplication::translate("Widget", "\345\217\214\344\272\272\345\257\271\346\210\230", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", 0));
        label_3->setText(QApplication::translate("Widget", "\345\257\206\347\240\201", 0));
        pushButton_3->setText(QApplication::translate("Widget", "\347\231\273\351\231\206", 0));
        pushButton_4->setText(QApplication::translate("Widget", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
