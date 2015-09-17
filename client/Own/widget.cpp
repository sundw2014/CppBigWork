#include "widget.h"
#include "ui_widget.h"
#include "own1.h"
#include "own2.h"
#include <QSound>
#include <QtGui>
#include <QtWidgets>
#include <string>
#include <fstream>
#include "protocol.hpp"
#include "client.hpp"
#include "unistd.h"

#define ROOMMAX 32
typedef struct
{
  unsigned int roomMax;
  char num[ROOMMAX];
}RoomTableInfo;

using namespace std;

#define ServerIP "104.131.145.13"
Client *client = NULL;

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
    else
    {
        int    sockfd;
        struct sockaddr_in servaddr;

        if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(10086);
        if(inet_pton(AF_INET, ServerIP , &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",ServerIP);
        exit(0);
        }

        if(::connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
        }
       if(client == NULL)
         client = new Client(sockfd);

       string userName = ui->user->text().toStdString();
       string passwd = ui->paw->text().toStdString();
       unsigned char tempLen[4] = {6,userName.length()+1,0,passwd.length()+1};

       client->sendFrame(tempLen,"SIGNUP",userName.c_str(),NULL,passwd.c_str());
       sleep(1);
       if(client->updateFrame())//3秒
         if(client->frame.cmd == string("OK"))
           QMessageBox::information(this, "ok","you can login now", QMessageBox::Ok);
         else
           QMessageBox::information(this, "error", "error",QMessageBox::Ok);
       else
           QMessageBox::information(this, "error", "error" , QMessageBox::Ok);
       delete client;
       client = NULL;
    }
}

void Widget::on_pushButton_3_clicked()  // 登陆
{
 if (ui->user->text().isEmpty() || ui->paw->text().isEmpty())
        QMessageBox::information(this, "error","no username or password", QMessageBox::Ok);
 else
 {
    int    sockfd;
    struct sockaddr_in servaddr;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10086);
    if( inet_pton(AF_INET, ServerIP , &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n",ServerIP);
    exit(0);
    }

    if(::connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }
    sleep(1);
    if(client == NULL)
        client = new Client(sockfd);

   string userName = ui->user->text().toStdString();
   string passwd = ui->paw->text().toStdString();
   unsigned char tempLen[4] = {5,userName.length()+1,0,passwd.length()+1};

   client->sendFrame(tempLen,"LOGIN",userName.c_str(),NULL,passwd.c_str());
   sleep(1);
   if(client->updateFrame())//3秒
     if(client->frame.cmd == string("SUCCESSFUL"))
     {
       RoomTableInfo roomList;
       memcpy(&roomList , client->receivedFrame->value3 , sizeof(RoomTableInfo));
       for(int i=0;i<roomList.roomMax;i++)
           printf("room%d:%d\r\n",i,roomList.num[i]);
       QMessageBox::information(this, "ok","login succeessfully", QMessageBox::Ok);
     }
     else
       QMessageBox::information(this, "error","error", QMessageBox::Ok);
   else
       QMessageBox::information(this, "error","error" , QMessageBox::Ok);
   delete client;
   client = NULL;
 }
}
