/********************************************************************************
** Form generated from reading UI file 'own1.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OWN1_H
#define UI_OWN1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Own1
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Own1)
    {
        if (Own1->objectName().isEmpty())
            Own1->setObjectName(QStringLiteral("Own1"));
        Own1->resize(840, 640);
        pushButton = new QPushButton(Own1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(700, 80, 131, 51));
        pushButton_2 = new QPushButton(Own1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(700, 170, 131, 51));

        retranslateUi(Own1);

        QMetaObject::connectSlotsByName(Own1);
    } // setupUi

    void retranslateUi(QDialog *Own1)
    {
        Own1->setWindowTitle(QApplication::translate("Own1", "Dialog", 0));
        pushButton->setText(QApplication::translate("Own1", "\345\233\236\346\224\276", 0));
        pushButton_2->setText(QApplication::translate("Own1", "\346\202\224\346\243\213", 0));
    } // retranslateUi

};

namespace Ui {
    class Own1: public Ui_Own1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OWN1_H
