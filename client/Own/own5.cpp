#include "own5.h"
#include "ui_own5.h"
#include "own6.h"
#include "own7.h"
#include <QtGui>
#include <QtWidgets>

Own5::Own5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Own5)
{
    ui->setupUi(this);
}

Own5::~Own5()
{
    delete ui;
}

void Own5::changelevel(int a)
{
    level = a;
}

void Own5::levelup()
{
    level+=1;
}

void Own5::on_pushButton_clicked() //第一关
{
    own6 o6;
    o6.name6 = name5;
    o6.setModal(true);
    o6.exec();
}

void Own5::on_pushButton_5_clicked()
{
    if(line != "1"){
        own7 o7;
        o7.name7 = name5;
        o7.setModal(true);
        o7.exec();
    }
    else QMessageBox::information(this, "ok",tr("不要心急哦，先把前面的关卡打通吧"), QMessageBox::Ok);
}

void Own5::on_pushButton_4_clicked()
{
    QMessageBox::information(this, "ok",tr("还没有更新哦"), QMessageBox::Ok);
}
