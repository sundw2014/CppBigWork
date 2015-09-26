#ifndef OWN6_H
#define OWN6_H

#include <QDialog>
#include "mType.h"

namespace Ui {
class own6;
}

class own6 : public QDialog
{
    Q_OBJECT

public:
    explicit own6(QWidget *parent = 0);
    ~own6();
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void AI(uint8 inp);
    QString name6;

private:
    Ui::own6 *ui;
    int a[16][16];
    int review;
    int Win(int, int);
    int win1(int, int);
    int win2(int, int);
    int win3(int, int);
    int win4(int, int);
    bool game;
};

#endif // OWN6_H
