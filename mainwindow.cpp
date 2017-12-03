#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*初始化窗口大小和位置*/
    ui->setupUi(this);
    ui->centralWidget->resize(1000, 800);
    ui->frame->setGeometry(10, 10, 600, 600);
    this->resize(1000, 800);
    ui->pushButton_reset->setGeometry(700, 20, 75, 25);     //重置
    ui->pushButton_test->setGeometry(700, 50, 75, 25);      //测试
    ui->pushButton_back->setGeometry(700, 120, 75, 25);      //悔棋
    ui->lineEdit_position->setGeometry(700,80, 150, 20);
    //ui->label_pic1->setGeometry(700, 120, 200, 200);
    //ui->label_pic2->setGeometry(700, 120, 200, 200);
    ui->label_playerN->setGeometry(700, 350, 150, 50);

    /*鼠标事件*/
    this->centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);
    ui->frame->setMouseTracking(true);


    /*按钮信号*/
    connect(ui->pushButton_reset, SIGNAL(clicked(bool)), this, SLOT(ResetBoard()));
    connect(ui->pushButton_test, SIGNAL(clicked(bool)), this, SLOT(TestBoard()));
    connect(ui->pushButton_back, SIGNAL(clicked(bool)), this, SLOT(RollBack()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*重置棋盘，棋盘数组清零，置为玩家回合*/
void MainWindow::ResetBoard()
{
    ui->frame->MyLocation.LocationClear();
    player = true;
    ui->frame->update();
}

void MainWindow::TestBoard()
{
    qDebug("test pressed");
}

/*悔棋响应函数*/
void MainWindow::RollBack()
{
    qDebug("RollBack pressed");
    if (ui->frame->LocationStack.empty())
    {
        return;
    }

    /*将栈内保存的坐标弹出*/
    ui->frame->LocUnit = ui->frame->LocationStack.top();
    ui->frame->MyLocation.Location[ui->frame->LocUnit.x][ui->frame->LocUnit.y]=0;
    ui->frame->LocationStack.pop();
    ui->frame->LocUnit = ui->frame->LocationStack.top();
    ui->frame->MyLocation.Location[ui->frame->LocUnit.x][ui->frame->LocUnit.y]=0;
    ui->frame->LocationStack.pop();
    ui->frame->update();
}

/*鼠标事件，鼠标移动时触发，显示当前frame上的坐标，用于计算棋盘的格子*/
void MainWindow::mouseMoveEvent ( QMouseEvent * event )
{
    QPoint pos = event->pos();
    ui->lineEdit_position->setText("Position: (" + QString::number(pos.x()) + ", " + QString::number(pos.y()) + ")");
}

void MainWindow::mousePressEvent ( QMouseEvent * event )
{

}

/*
 * 鼠标事件，鼠标抬起时触发
 * 首先判断鼠标是否在棋盘（frame）上
 * 然后判断当前棋盘位置是否有棋子，玩家落子，AI行动，判断输赢
*/
void MainWindow::mouseReleaseEvent ( QMouseEvent * event )
{
    QPoint pos = event->pos();
    int Px;
    int Py;
    Px=(pos.x()-10)/60;     //坐标对应数组
    Py=(pos.y()-10)/60;

    if (ui->frame->MyLocation.Location[Px][Py] == 0 &&
            pos.x()<=610 && pos.y()<=610)
    {
        /*玩家落子*/
        ui->frame->MyLocation.Location[Px][Py] = 2;

        ui->frame->LocUnit.x=Px;
        ui->frame->LocUnit.y=Py;
        ui->frame->LocationStack.push(ui->frame->LocUnit);  //将玩家落子位置压栈

        /*AI回合*/
        ui->frame->ComputerTurn();


        ui->frame->update();
        /*判断输赢，如果赢了调胜利函数*/
        bool iswin = ui->frame->isWin(&player);
        if (iswin == true)
        {
            PlayerWinning();
        }

    }
}

/*
 * 打开胜利窗口，显示信息和两个按钮
 * 再来一次，重置棋盘
 * 退出，退出程序
*/
void MainWindow::PlayerWinning()
{
    Winning PlayerWin(player, this);

    int ret = PlayerWin.exec(); //接收胜利窗口关闭时的返回值
    if (ret == PlayerWin.Accepted)
    {
        ResetBoard();
        player = false;
    }
    else if(ret == PlayerWin.Rejected)
    {
        exit(0);
    }

}

