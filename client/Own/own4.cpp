#include "own4.h"
#include "ui_own4.h"
#include "time.h"
#include "own2.h"
#include <QtGui>
#include <QtWidgets>
#include "AI.h"

own4::own4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::own4)
{
    m = 0;
    ui->setupUi(this);
}

own4::~own4()
{
    delete ui;
}

void own4::on_pushButton_clicked()
{
    if(m != 0) QMessageBox::information(this,"warning","You have set color", QMessageBox::Ok);
    else {
        m = 1;
        QMessageBox::information
                (this,"ok","succeed", QMessageBox::Ok);
    }
}


void own4::on_pushButton_2_clicked()
{
    if(m != 0) QMessageBox::information(this,"warning","You have set color", QMessageBox::Ok);
    else  {
        m = 2;
        QMessageBox::information
                (this,"ok","succeed", QMessageBox::Ok);
    }
}

void own4::on_pushButton_3_clicked()
{
    if(m == 0) QMessageBox::information(this,"warning","You haven't set color", QMessageBox::Ok);
    else{
        Own2 o2;
        o2.choose = m;
        if(m==2) {
            o2.a[8][8]=1;
            ChessBoard::AIInit(1,ui->lineEdit->text().toInt());
        }
        if(m==1){
            ChessBoard::AIInit(2,ui->lineEdit->text().toInt());
        }
        o2.setModal(true);
        o2.exec();
    }
}
