#include "roomlist.h"
#include "ui_roomlist.h"
#include "protocol.hpp"
#include "client.hpp"
#include <sstream>
#include "own1.h"
#include "windows.h"
#include"stdio.h"
#include "qthread.h"

RoomList::RoomList(Client &mclient,RoomTableInfo &list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomList),
    client(mclient),
    roomList(list)
{
    ui->setupUi(this);
    for(unsigned char pos=0;pos<ROOMMAX;pos++)
    {
        stringstream converter;
        converter<<(int)pos<<": "<<(int)roomList.num[pos];

        QTableWidgetItem *item0 = new QTableWidgetItem;
        item0->setText(QString::fromStdString(converter.str()));
        ui->tableWidget->setItem(pos/6,pos%6,item0);
        converter.flush();
    }
}

RoomList::~RoomList()
{
    delete ui;
}

void RoomList::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    unsigned char row = item->row(),col = item->column();
    unsigned char tempLen[4] = {6,1,0,0};
    printf("%d,%d\r\n",row,col);
    unsigned char *newINP = new unsigned char;
    *newINP = row*6+col;
    client.sendFrame(tempLen,"JOININ",(char *)newINP);
    Sleep(7000);
    if(client.updateFrame())
    {
        if(client.frame.cmd == string("OK1"))
        {
            Own1 *o1 = new Own1(client,1,this);
            o1->setModal(true);
            o1->gameControl->start();
            this->close();
            o1->exec();
        }
        if(client.frame.cmd == string("OK2"))
        {
            Own1 *o1 = new Own1(client,2,this);
            o1->setModal(true);
            o1->gameControl->start();
            this->close();
            o1->exec();
        }
    }
}
