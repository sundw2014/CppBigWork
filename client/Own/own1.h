#ifndef OWN1_H
#define OWN1_H

#include <QDialog>
#include <QSound>
#include "statemachine.h"
#include "mType.h"

class StateMachine;

namespace Ui {
class Own1;
}

class Own1 : public QDialog
{
    Q_OBJECT

public:
    explicit Own1(Client &mclient,int myTurn,QWidget *parent = 0);
    ~Own1();
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    int myTurn(){return _myTurn;}
    StateMachine *gameControl;
    int Win(int, int);
    bool inp(uint8 inp,uint8 turn)
    {
        if(a[inp/16][inp%16]==0)
            a[inp/16][inp%16] = turn;
        else
            return false;
        update();
        return true;
    }
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Own1 *ui;
    int a[16][16];
    int review = 0;
    int win1(int, int);
    int win2(int, int);
    int win3(int, int);
    int win4(int, int);
    int player;
    int users;
    int _myTurn;
    bool check = true;
    Client &client;
};

class save
{
public:
    int _x;
    int _y;
    save ()
    {
        _x = 0;
        _y = 0;
    }
    void inisave(int a,int b)
    {
        this->_x = a;
        this->_y = b;
    }

};

#endif // OWN1_H
