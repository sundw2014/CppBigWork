#include "own7.h"
#include "ui_own7.h"
#include <QtGui>
#include <QtWidgets>
#include "time.h"
#include "AI.h"
#include <QSound>

own7::own7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::own7)
{
    review = 0;
    game = true;
    ui->setupUi(this);
    resize(680 , 680);
    memset(a, 0, 16 * 16 * sizeof(int));
    a[2][8]=a[2][9]=a[4][11]=a[5][7]=a[5][8]=a[5][10]=a[6][6]=a[6][11]
            =a[7][7]=a[7][9]=a[7][11]=a[8][9]=a[8][10]=a[9][10]=a[10][10]
            =a[10][11]=2;
    a[3][9]=a[4][8]=a[4][9]=a[4][10]=a[5][9]=a[5][10]=a[6][7]
            =a[6][8]=a[6][9]=a[6][10]=a[7][8]=a[7][10]=a[8][8]
            =a[8][12]=a[9][9]=a[9][11]=1;
}

own7::~own7()
{
    delete ui;
}

void own7::paintEvent(QPaintEvent *)
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

void own7::mouseReleaseEvent(QMouseEvent *e)
{
    if(game){
      int x, y;
      if(e->x() >= 20 && e->x() < 660 && e->y() >= 20 && e->y() < 660)
      {
        x = (e->x() - 20) / 40;
        y = (e->y() - 20) / 40;

        if (!a[x][y])
        {
            a[x][y] = 1;
            repaint();
            QSound::play("image//1.wav");
            AI(x*16+y);
        }
        if(Win(x, y))
        {
           QMessageBox::information(this, "Win", "Win", QMessageBox::Ok);
           QFile date(name7);
           date.open(QFile::ReadWrite);
           QTextStream in (&date);
           QString s1 = in.readLine();
           QString s2 = in.readLine();
           date.remove();
           QFile file(name7);
           file.open(QIODevice::Text|QFile::WriteOnly|QIODevice::Truncate);
           QTextStream tin (&file);
           tin << s1 << '\n';
           if(s2 == "2") s2 = "3";
           tin << s2 ;
           file.close();
        }
        update();
      }
    }
    else QMessageBox::information(this, "STOP", "this game is over", QMessageBox::Ok);
}

int own7::Win(int x, int y)                            // 胜利条件
{

     return win1(x, y) || win2(x, y) || win3(x, y) || win4(x ,y);
     game = false;
}

int own7::win1(int x, int y)
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

int own7::win2(int x, int y)
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

int own7::win3(int x, int y)
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

int own7::win4(int x, int y)
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


void own7::AI(uint8 inp)
{
    ChessBoard *rootChessBoard = new ChessBoard(a,inp);
    int16 output = rootChessBoard->run();
    delete rootChessBoard;

    int m = output / 16;
    int n = output % 16;
    int q = 2;

     if(a[m][n] == 0 )
     {
         a[m][n] = q;
         if(Win(m, n))
         {
             update();
             QMessageBox::information(this, "Lose", "Lose", QMessageBox::Ok);
         }
      }
}
