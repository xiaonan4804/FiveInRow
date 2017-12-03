#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <string>
#include <QImage>
#include <QPixmap>
#include "winning.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );

private slots:
    void ResetBoard();
    void TestBoard();
    void RollBack();

private:
    void PlayerWinning();
    Ui::MainWindow *ui;
    bool player = true;    //player: true 2   AI:false 1

};

#endif // MAINWINDOW_H
