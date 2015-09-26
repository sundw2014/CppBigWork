#ifndef OWN5_H
#define OWN5_H

#include <QDialog>

namespace Ui {
class Own5;
}

class Own5 : public QDialog
{
    Q_OBJECT

public:
    explicit Own5(QWidget *parent = 0);
    ~Own5();
    void changelevel(int a);
    void levelup();
    QString name5;
    QString line;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Own5 *ui;
    int level;
};

#endif // OWN5_H
