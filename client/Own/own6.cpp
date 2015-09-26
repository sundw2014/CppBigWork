#include "own6.h"
#include "ui_own6.h"
#include <QtGui>
#include <QtWidgets>
#include "time.h"
#include "AI.h"
#include <QSound>

own6::own6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::own6)
{
    review = 0;
    game = true;
    ui->setupUi(this);
    resize(680 , 680);
    memset(a, 0, 16 * 16 * sizeof(int));
    a[8][8] = a[8][7] = a[9][6] = a[5][8] = a[5][7] = a[7][4] = a[4][10]
            = a[9][11] = a[11][9] = a[11][10] = 1;
    a[7][8] = a[7][7] = a[7][6] = a[6][7] = a[5][9] = a[8][9] = a[9][7]
            = a[9][8] = a[9][9] = a[10][9] = a[11][6] = 2;
}

own6::~own6()
{
    delete ui;
}

void own6::paintEvent(QPaintEvent *)
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

void own6::mouseReleaseEvent(QMouseEvent *e)
{
    if(game){
      int x, y;
      if(e->x() >= 20 && e->x() < 660 && e->y() >= 20 && e->y() < 660)
      {
        x = (e->x() - 20) / 40;
        y = (e->y() - 20) / 40;

        if (!a[x][y])
        {
            QSound::play("image//1.wav");
            a[x][y] = 1;
            repaint();
            AI(x*16+y);
        }
        if(Win(x, y))
        {
           QMessageBox::information(this, "Win", "Win", QMessageBox::Ok);
           QFile date(name6);
           date.open(QFile::ReadWrite);
           QTextStream in (&date);
           QString s1 = in.readLine();
           QString s2 = in.readLine();
           date.remove();
           QFile file(name6);
           file.open(QIODevice::Text|QFile::WriteOnly|QIODevice::Truncate);
           QTextStream tin (&file);
           tin << s1 << '\n';
           if(s2 == "1") s2 = "2";
           tin << s2 ;
           file.close();
        }
        update();
      }
    }
    else QMessageBox::information(this, "STOP", "this game is over", QMessageBox::Ok);
}

int own6::Win(int x, int y)                            // 胜利条件
{

     return win1(x, y) || win2(x, y) || win3(x, y) || win4(x ,y);
     game = false;
}

int own6::win1(int x, int y)
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

int own6::win2(int x, int y)
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

int own6::win3(int x, int y)
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

int own6::win4(int x, int y)
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


void own6::AI(uint8 inp)
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
