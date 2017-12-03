#ifndef WINNING_H
#define WINNING_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Winning;
}

class Winning : public QDialog
{
    Q_OBJECT

public:
    explicit Winning(bool Player, QWidget *parent = 0);
    ~Winning();

private slots:
    int pushOK();
    int pushQuit();

private:
    Ui::Winning *ui;
};

#endif // WINNING_H
