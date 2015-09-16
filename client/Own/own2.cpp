#include "own2.h"
#include "ui_own2.h"
#include <QtGui>
#include <QtWidgets>
#include "time.h"
#include <unistd.h>

Own2::Own2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Own2)
{
    ui->setupUi(this);
    resize(880 , 680);
    memset(a, 0, 16 * 16 * sizeof(int));
    for(uint8 i=1;i<maxDepth+1;i++)
        hashValues[i] = new std::vector<ZobristNode>;
    numProcessors = sysconf(_SC_NPROCESSORS_CONF); //更新cpu核心数
    player = 0;
    QMessageBox::information(this, "Wait", "Please dicide your color(black first)", QMessageBox::Ok);
}

Own2::~Own2()
{
    delete ui;
}

void Own2::paintEvent(QPaintEvent *)
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

void Own2::mouseReleaseEvent(QMouseEvent *e)
{
    if(choose == 0) QMessageBox::information(this,"warning","You haven't set color", QMessageBox::Ok);
    else{
      int x, y;
      if(e->x() >= 20 && e->x() < 660 && e->y() >= 20 && e->y() < 660)
      {
        x = (e->x() - 20) / 40;
        y = (e->y() - 20) / 40;

        if (!a[x][y])
        {
            a[x][y] = choose;
            realPly++;
            AI(x*16+y);
        }
        if(Win(x, y))
        {
            update();
            int m = choose;
            if (m==1) QMessageBox::information(this, "Win", "Black Win", QMessageBox::Ok);

            if (m==2) QMessageBox::information(this, "Win", "White Win", QMessageBox::Ok);
        }

      }
    }
    update();
}

int Own2::Win(int x, int y)                            // 胜利条件
{
     return win1(x, y) || win2(x, y) || win3(x, y) || win4(x ,y);
}

int Own2::win1(int x, int y)
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

int Own2::win2(int x, int y)
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

int Own2::win3(int x, int y)
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

int Own2::win4(int x, int y)
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

void Own2::on_pushButton_clicked()
{
    if(choose != 0) QMessageBox::information(this,"warning","You have set color", QMessageBox::Ok);
    else choose = 1;
}

void Own2::on_pushButton_2_clicked()
{
    if(choose != 0) QMessageBox::information(this,"warning","You have set color", QMessageBox::Ok);
    else {
      choose = 2;
      (time(NULL)) ;//通过系统时间初始化随机数种子
      int m = rand()%16;
      int n = rand()%16;
      a[m][n] = 1;
    }
}

void Own2::AI(uint8 inp)
{
    hash = ZobristHash(hash,inp,choose,0);
    ChessBoard *rootChessBoard = new ChessBoard(a,hash);
    int16 output = rootChessBoard->run();
    delete rootChessBoard;
    int p = 0;
//    while (p == 0)
//    {
//        (time(NULL)) ;//通过系统时间初始化随机数种子
        int m = output / 16;
        int n = output % 16;
        int q = 3-choose;

        if(a[m][n] == 0 )
        {
            a[m][n] = q;
            p = 1;
            if(Win(m, n))
            {
                update();
                int ch = choose;
                if (ch==2) QMessageBox::information(this, "Win", "Black Win", QMessageBox::Ok);

                if (ch==1) QMessageBox::information(this, "Win", "White Win", QMessageBox::Ok);
            }
        }
//    }
        realPly++;
}
