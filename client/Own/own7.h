#ifndef OWN7_H
#define OWN7_H

#include <QDialog>
#include "mType.h"

namespace Ui {
class own7;
}

class own7 : public QDialog
{
    Q_OBJECT

public:
    explicit own7(QWidget *parent = 0);
    ~own7();
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void AI(uint8 inp);
    QString name7;

private:
    Ui::own7 *ui;
    int a[16][16];
    int review;
    int Win(int, int);
    int win1(int, int);
    int win2(int, int);
    int win3(int, int);
    int win4(int, int);
    bool game;
};

#endif // OWN7_H
