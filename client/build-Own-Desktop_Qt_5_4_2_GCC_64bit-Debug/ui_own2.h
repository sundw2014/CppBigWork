/********************************************************************************
** Form generated from reading UI file 'own2.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OWN2_H
#define UI_OWN2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Own2
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Own2)
    {
        if (Own2->objectName().isEmpty())
            Own2->setObjectName(QStringLiteral("Own2"));
        Own2->resize(840, 640);
        pushButton = new QPushButton(Own2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(700, 60, 101, 51));
        pushButton_2 = new QPushButton(Own2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(700, 150, 101, 51));

        retranslateUi(Own2);

        QMetaObject::connectSlotsByName(Own2);
    } // setupUi

    void retranslateUi(QDialog *Own2)
    {
        Own2->setWindowTitle(QApplication::translate("Own2", "Dialog", 0));
        pushButton->setText(QApplication::translate("Own2", "\346\210\221\350\246\201\347\224\250\351\273\221\345\255\220", 0));
        pushButton_2->setText(QApplication::translate("Own2", "\346\210\221\350\246\201\347\224\250\347\231\275\345\255\220", 0));
    } // retranslateUi

};

namespace Ui {
    class Own2: public Ui_Own2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OWN2_H
