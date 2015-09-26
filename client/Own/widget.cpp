#include "widget.h"
#include "ui_widget.h"
#include "own1.h"
#include "own2.h"
#include "own3.h"
#include "own4.h"
#include <QSound>
#include <QtGui>
#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "login.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    edit = false;
    showpass = false;
    music_num = 300;
    play_now = true;

    ui->setupUi(this);
    play[0]=new QSound("image//2.wav");
    play[1]=new QSound("image//3.wav");
    play[2]=new QSound("image//4.wav");
    play[0]->setLoops(1000);
    play[1]->setLoops(1000);
    play[2]->setLoops(1000);
    play[0]->play();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()  // 双人游戏
{
//    if(edit){
        Login login;
        login.setModal(true);
        this->close();
        login.exec();
//    }
//    else QMessageBox::information(this, "error","you haven't login", QMessageBox::Ok);
}

void Widget::on_pushButton_clicked() //单人对战
{
    if(edit){
        own4 o4;
        o4.setModal(true);
        o4.exec();
    }
    else QMessageBox::information(this, "error","you haven't login", QMessageBox::Ok);
}

void Widget::on_pushButton_4_clicked() // 注册
{
    if (ui->user->text().isEmpty() || ui->paw->text().isEmpty())
        QMessageBox::information(this, "error","no username or password", QMessageBox::Ok);
    if (ui->user->text().length() > 20)
        QMessageBox::information(this, "error",tr("用户名过长请重新输入"), QMessageBox::Ok);
    if (ui->paw->text().length() < 6 || ui->paw->text().length() >50)
        QMessageBox::information(this, "error",tr("密码长度应在6-50字节之间"), QMessageBox::Ok);
    else{
       QString str1 = ui->user->text();
       QString str2 = ".txt";
       QString str3 = str1 + str2;
       QString str4 = ui->paw->text();
       int i = 1;
       QFile data(str3);
           if(data.open(QIODevice::Text|QFile::WriteOnly|QIODevice::Truncate)){
               QTextStream out(&data);
               out<<str4;
               out<<qSetFieldWidth(1)<<'\n';
               out<<qSetFieldWidth(1)<<i;
           }
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
        str3 = str1 + str2;
        QString str4;
        if(QFile::exists(str3)){
            QFile date(str3);
            date.open(QFile::ReadOnly);
            QTextStream in (&date);
            str4 = in.readLine();
            thefile = in.readLine();
            if(str4 == ui->paw->text()){
                QMessageBox::information(this, "ok",tr("您已成功登陆"), QMessageBox::Ok);
                edit = true;
            }
            else
                QMessageBox::information(this, "error","wrong password", QMessageBox::Ok);
            date.close();
        }
        else
             QMessageBox::information(this, "error","wrong username", QMessageBox::Ok);
    }
}

void Widget::on_pushButton_5_clicked()
{
    if(showpass) showpass = false;
    else showpass = true;

    if(showpass) ui->paw->setEchoMode(QLineEdit::Password);
    else ui->paw->setEchoMode(QLineEdit::Normal);

    QMessageBox::information(this, "ok","change", QMessageBox::Ok);
    update();
}

void Widget::on_pushButton_6_clicked() // 残局对战
{
    if(edit){
        own3=new Own3;
        own3->name3 = str3;
        own3->thename = thefile;
        own3->show();
        }
    else QMessageBox::information(this, "error","you haven't login", QMessageBox::Ok);
}


void Widget::on_pushButton_8_clicked() //上一首
{
    music_num = music_num - 1;
    play[(music_num-1)%3]->stop();
    play[music_num%3]->play();
}

void Widget::on_pushButton_7_clicked() //下一首
{
    play[music_num%3]->stop();
    music_num = music_num + 1;
    play[music_num%3]->play();
}


void Widget::on_pushButton_9_clicked()
{
    if(play_now){
        play[music_num%3]->stop();
        play_now=false;
    }
    else{
        play[music_num%3]->play();
        play_now=true;
    }
}
