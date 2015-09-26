#ifndef OWN4_H
#define OWN4_H

#include <QDialog>

namespace Ui {
class own4;
}

class own4 : public QDialog
{
    Q_OBJECT

public:
    explicit own4(QWidget *parent = 0);
    ~own4();
    int m;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::own4 *ui;

};

#endif // OWN4_H
