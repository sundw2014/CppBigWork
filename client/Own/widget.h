#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSound>
#include "own3.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString str3;
    QString thefile;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::Widget *ui;
    bool edit;
    bool showpass;
    Own3 *own3;
    QSound *play[3];
    int music_num;
    bool play_now;
};

#endif // WIDGET_H
