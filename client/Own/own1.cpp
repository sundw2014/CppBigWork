#include "own1.h"
#include "ui_own1.h"
#include <QtGui>
#include <QtWidgets>
#include <QSound>
#include "widget.h"
#include "unistd.h"

Own1::Own1(Client &mclient,int myTurn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Own1),
    client(mclient),
    _myTurn(myTurn)
{
    ui->setupUi(this);
    resize(880 , 680);
    memset(a, 0, 16 * 16 * sizeof(int));
    player = 0;
    gameControl = new StateMachine(*this,client);
    if(_myTurn==1)
        gameControl->setState(WAIT);
    else
        gameControl->setState(OTHSTURN);
    //QMessageBox::information(this, "Win", users, QMessageBox::Ok);
}

Own1::~Own1()
{
    delete ui;
}

save file[300];

void Own1::paintEvent(QPaintEvent *)
{
    QPainter d(this);
    int i,j;
    for (i=0 ; i<17 ; i++)
    {
       d.drawLine(20 , 20+40* i ,660 , 20+40*i);
       d.drawLine(20 + i * 40, 20, 20 + i * 40, 660);
    }

    QBrush brush(Qt::SolidPattern);
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            if (a[i][j] == 1)
            {
                brush.setColor(Qt::black);
                d.setBrush(brush);
                d.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
            }
            else if (a[i][j] == 2)
            {
                brush.setColor(Qt::white);
                d.setBrush(brush);
                d.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
            }
        }
    }

}

void Own1::mouseReleaseEvent(QMouseEvent *e)
{
    if(gameControl->getSTATE()==YOURTURN)
    {
        int x, y;
        if(e->x() >= 20 && e->x() < 660 && e->y() >= 20 && e->y() < 660)
        {
            x = (e->x() - 20) / 40;
            y = (e->y() - 20) / 40;

            if (!a[x][y])
            {
                a[x][y] = _myTurn;
                file[player].inisave(x , y);
                QSound::play("D://1.wav");
                unsigned char tempLen[4] = {6,1,0,0};
                unsigned char *newINP = new unsigned char;
                *newINP = x*16+y;
                client.sendFrame(tempLen,"NEWINP",(char *)newINP);
                sleep(1);
                delete newINP;
                gameControl->setState(OTHSTURN);
            }
            if(Win(x, y))
            {
                update();
                QMessageBox::information(this, "win", "YOU WIN", QMessageBox::Ok);
                gameControl->setState(OVER);
            }
            update();
            gameControl->runOnce();
        }
        update();
    }
//    if (check){
//    int x, y;
//    if(e->x() >= 20 && e->x() < 660 && e->y() >= 20 && e->y() < 660)
//    {
//        x = (e->x() - 20) / 40;
//        y = (e->y() - 20) / 40;

//        if (!a[x][y])
//        {
//            a[x][y] = player % 2 + 1;
//            file[player].inisave(x , y);
//            player +=1;
//            QSound::play("D://1.wav");
//        }
//        if(Win(x, y))
//        {
//            update();
//            int m = player % 2 + 1;
//            if (m==2) QMessageBox::information(this, "Win", "Black Win", QMessageBox::Ok);

//            if (m==1) QMessageBox::information(this, "Win", "White Win", QMessageBox::Ok);
//        }

//    }
//    update();
//    }
//    else QMessageBox::information(this, "error", "Stop do this", QMessageBox::Ok);
}

int Own1::Win(int x, int y)                            // 胜利条件
{
     return win1(x, y) || win2(x, y) || win3(x, y) || win4(x ,y);
}

int Own1::win1(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(y - i >= 0 &&
           y + 4 - i <= 0xF &&
           a[x][y - i] == a[x][y + 1 - i] &&
           a[x][y - i] == a[x][y + 2 - i] &&
           a[x][y - i] == a[x][y + 3 - i] &&
           a[x][y - i] == a[x][y + 4 - i])
        return 1;
    }
    return 0;
}

int Own1::win2(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(x - i >= 0 &&
           x + 4 - i <= 0xF &&
           a[x - i][y] == a[x + 1 - i][y] &&
           a[x - i][y] == a[x + 2 - i][y] &&
           a[x - i][y] == a[x + 3 - i][y] &&
           a[x - i][y] == a[x + 4 - i][y])
           return 1;
    }
    return 0;
}

int Own1::win3(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(x - i >= 0 &&
           y - i >= 0 &&
           x + 4 - i <= 0xF &&
           y + 4 - i <= 0xF &&
           a[x - i][y - i] == a[x + 1 - i][y + 1 - i] &&
           a[x - i][y - i] == a[x + 2 - i][y + 2 - i] &&
           a[x - i][y - i] == a[x + 3 - i][y + 3 - i] &&
           a[x - i][y - i] == a[x + 4 - i][y + 4 - i])
           return 1;
    }
    return 0;
}

int Own1::win4(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
   {
        if(x + i <= 0xF &&
           y - i >= 0 &&
           x - 4 + i >= 0 &&
           y + 4 - i <= 0xF &&
           a[x + i][y - i] == a[x - 1 + i][y + 1 - i] &&
           a[x + i][y - i] == a[x - 2 + i][y + 2 - i] &&
           a[x + i][y - i] == a[x - 3 + i][y + 3 - i] &&
           a[x + i][y - i] == a[x - 4 + i][y + 4 - i])
           return 1;
    }
    return 0;
}

void Own1::on_pushButton_clicked()
{

    check = false;
    if(review == 0) memset(a, 0, 16 * 16 * sizeof(int));
    if(review >= player)
    {
        QMessageBox::information(this,"stop","no more steps",QMessageBox::Ok);
    }

    if(review < player)
    {
        a[file[review]._x][file[review]._y] = review%2 + 1;
        review++;
        update();
    }
}

void Own1::on_pushButton_2_clicked()
{
    a[file[(player-1)]._x][file[(player-1)]._y] = 0;
    a[file[(player-2)]._x][file[(player-2)]._y] = 0;
    player = player - 2;
    update();
}
