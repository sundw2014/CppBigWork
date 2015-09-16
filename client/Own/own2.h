#ifndef OWN2_H
#define OWN2_H
#include "AI.h"

#include <QDialog>

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
    void AI(uint8 inp);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Own2 *ui;
    int a[16][16];
    int review = 0;
    int Win(int, int);
    int win1(int, int);
    int win2(int, int);
    int win3(int, int);
    int win4(int, int);
    int choose = 0;
    int player;
};

#endif // OWN2_H
