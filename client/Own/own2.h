#ifndef OWN2_H
#define OWN2_H

#include <QDialog>
#include "mType.h"

namespace Ui {
class Own2;
}

class Own2 : public QDialog
{
    Q_OBJECT

public:
    explicit Own2(QWidget *parent = 0);
    ~Own2();
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void AI(uint8);
    int choose;
    int a[16][16];
    //void AI(uint8 inp);

private:
    Ui::Own2 *ui;

    int review;
    int Win(int, int);
    int win1(int, int);
    int win2(int, int);
    int win3(int, int);
    int win4(int, int);
    int player;
    bool game;
};

#endif // OWN2_H
