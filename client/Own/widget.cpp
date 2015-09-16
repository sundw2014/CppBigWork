#include "widget.h"
#include "ui_widget.h"
#include "own1.h"
#include "own2.h"
#include <QSound>
#include <QtGui>
#include <QtWidgets>
#include <string>
#include <fstream>
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QSound::play("D://2.wav");
    ui->paw->setEchoMode(QLineEdit::Password);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    if(edit){
        Own1 o1;
        o1.setModal(true);
        o1.exec();
    }
    else QMessageBox::information(this, "error","you haven't login", QMessageBox::Ok);
}

void Widget::on_pushButton_clicked()
{
    if(edit){
        Own2 o2;
        o2.setModal(true);
        o2.exec();
    }
    else QMessageBox::information(this, "error","you haven't login", QMessageBox::Ok);
}

void Widget::on_pushButton_4_clicked() // 注册
{
    if (ui->user->text().isEmpty() || ui->paw->text().isEmpty())
        QMessageBox::information(this, "error","no username or password", QMessageBox::Ok);
    else{
       QString str1 = ui->user->text();
       QString str2 = ".txt";
       QString str3 = str1 + str2;
       QFile date(str3);
       date.open(QFile::WriteOnly);
       QTextStream out (&date);
       out << ui->paw->text() << endl;
       date.close();
       ui->user->clear();
       ui->paw->clear();
       QMessageBox::information(this, "ok","you can play now", QMessageBox::Ok);
    }
}

void Widget::on_pushButton_3_clicked()  // 登陆
{
    if (ui->user->text().isEmpty() || ui->paw->text().isEmpty())
        QMessageBox::information(this, "error","no username or password", QMessageBox::Ok);
    else{
        QString str1 = ui->user->text();
        QString str2 = ".txt";
        QString str3 = str1 + str2;
        QString str4;
        if(QFile::exists(str3)){
            QFile date(str3);
            date.open(QFile::ReadOnly);
            QTextStream in (&date);
            str4 = in.readLine();
            if(str4 == ui->paw->text()){
                QMessageBox::information(this, "ok","succeed", QMessageBox::Ok);
                edit = true;
            }
            else
                QMessageBox::information(this, "error","wrong password", QMessageBox::Ok);
        }
        else
             QMessageBox::information(this, "error","wrong username", QMessageBox::Ok);
    }
}
