#ifndef ROOMLIST_H
#define ROOMLIST_H

#include <QDialog>
#include "client.hpp"
#include "protocol.hpp"
#include "ui_roomlist.h"

namespace Ui {
class RoomList;
}

class RoomList : public QDialog
{
    Q_OBJECT

public:
    explicit RoomList(Client &cient,RoomTableInfo &list,QWidget *parent = 0);
    ~RoomList();

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::RoomList *ui;
    RoomTableInfo &roomList;
    Client &client;
};

#endif // ROOMLIST_H
