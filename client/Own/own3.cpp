#include "own3.h"
#include "ui_own3.h"
#include "own5.h"
#include "AI.h"

Own3::Own3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Own3)
{
    ui->setupUi(this);
}

Own3::~Own3()
{
    delete ui;
}

void Own3::on_pushButton_clicked()
{
    Own5 o5;
    o5.name5 = name3;
    o5.line = thename;
    uint8 level = ui->lineEdit->text().toInt();
    ChessBoard::AIInit(2,level);
    o5.setModal(true);
    o5.exec();
}
