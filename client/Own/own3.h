#ifndef OWN3_H
#define OWN3_H

#include <QDialog>

namespace Ui {
class Own3;
}

class Own3 : public QDialog
{
    Q_OBJECT

public:
    explicit Own3(QWidget *parent = 0);
    ~Own3();
    QString name3;
    QString thename;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Own3 *ui;
};

#endif // OWN3_H
