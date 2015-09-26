#include "login.h"
#include "ui_login.h"
#include "own1.h"
#include "own2.h"
#include <QtGui>
#include <string>
#include <fstream>
#include "protocol.hpp"
#include "client.hpp"
#include "windows.h"
#include "roomlist.h"
#include "ui_roomlist.h"
#include <QtWidgets>

using namespace std;

#define ServerIP "104.131.145.13"      //"127.0.0.1"
Client *client = NULL;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->passwdEdit->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    if (ui->usernameEdit->text().isEmpty() || ui->passwdEdit->text().isEmpty())
           QMessageBox::information(this, "error","no username or password", QMessageBox::Ok);
    else
    {
       WSAData wsadata;
       WSAStartup(MAKEWORD(2,2),&wsadata);
       int    sockfd;
       struct sockaddr_in servaddr;

       if( (sockfd = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
       printf("create socket error: %s(errno: %d)\r\n", strerror(errno),errno);
       exit(0);
       }

       memset(&servaddr, 0, sizeof(servaddr));
       servaddr.sin_family = AF_INET;
       servaddr.sin_port = htons(10086);
       servaddr.sin_addr.S_un.S_addr=inet_addr(ServerIP);

       if(::connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
       printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
       exit(0);
       }
       Sleep(1000);
       if(client == NULL)
           client = new Client(sockfd);

      string userName = ui->usernameEdit->text().toStdString();
      string passwd = ui->passwdEdit->text().toStdString();
      unsigned char tempLen[4] = {5,userName.length()+1,0,passwd.length()+1};

      client->sendFrame(tempLen,"LOGIN",userName.c_str(),NULL,passwd.c_str());
      Sleep(1000);
      if(client->updateFrame())//3秒
        if(client->frame.cmd == string("SUCCESSFUL"))
        {
          RoomTableInfo *roomList = new RoomTableInfo;
          memcpy(roomList , client->receivedFrame->value3 , sizeof(RoomTableInfo));
   //       for(int i=0;i<roomList->roomMax;i++)
   //           printf("room%d:%d\r\n",i,roomList.num[i]);
   //       QMessageBox::information(this, "ok","login succeessfully", QMessageBox::Ok);
          RoomList roomTable(*client,*roomList,0);
          delete roomList;
          this->close();
          roomTable.exec();
        }
        else
          QMessageBox::information(this, "error","error", QMessageBox::Ok);
      else
          QMessageBox::information(this, "error","error" , QMessageBox::Ok);
      delete client;
      client = NULL;
    }
}

void Login::on_signup_clicked()
{
    if (ui->usernameEdit->text().isEmpty() || ui->passwdEdit->text().isEmpty())
        QMessageBox::information(this, "error","no username or password", QMessageBox::Ok);
    else
    {
        int    sockfd;
        struct sockaddr_in servaddr;
        WSAData wsadata;
        WSAStartup(MAKEWORD(2,2),&wsadata);

        if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(10086);
        servaddr.sin_addr.S_un.S_addr=inet_addr(ServerIP);

        if(::connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == INVALID_SOCKET){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
        }
       if(client == NULL)
         client = new Client(sockfd);

       string userName = ui->usernameEdit->text().toStdString();
       string passwd = ui->passwdEdit->text().toStdString();
       unsigned char tempLen[4] = {6,userName.length()+1,0,passwd.length()+1};

       client->sendFrame(tempLen,"SIGNUP",userName.c_str(),NULL,passwd.c_str());
       Sleep(1000);
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
