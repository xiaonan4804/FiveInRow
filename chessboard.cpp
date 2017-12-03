#include "chessboard.h"
#include <QPainter>
#include <QDebug>
#include <math.h>

ChessBoard::ChessBoard(QWidget *parent)
    : QFrame(parent)
{

}

/*
 * 绘图事件
 * 画棋盘格子，根据棋盘数组画棋盘上点的位置
*/
void ChessBoard::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();

    QColor LineColor(28, 23, 179);     //green
    QColor RedColor(255, 0, 0);     //green
    QColor GreenColor(0, 255, 0);     //green
    QPen pen(LineColor);
    pen.setWidth(2);
    painter.setPen(pen);

    //画棋盘格子
    for (int i=0; i<=width; i+=60)
    {
        painter.drawLine(0, i, width, i);
        painter.drawLine(i, 0, i, height);
    }

    //根据棋盘数组画棋盘上点的位置
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (MyLocation.Location[i][j] == 1)     //电脑棋子位置
            {
                QPen pen(RedColor);
                pen.setWidth(20);
                painter.setPen(pen);
                painter.drawEllipse(i*60+20, j*60+20, 20, 20);
            }
            if (MyLocation.Location[i][j] == 2)     //玩家棋子位置
            {
                QPen pen(GreenColor);
                pen.setWidth(20);
                painter.setPen(pen);
                painter.drawEllipse(i*60+20, j*60+20, 20, 20);
            }
        }

    }
}

/*判断横竖斜，是否有5个连续棋子
输入：坐标和玩家， 输出1/0*/
int ChessBoard::fineFive(int x, int y, int turn)
{
    int count1=0;
    int count2=0;
    int count3=0;
    for (int i=0; i<5; i++)
    {
        if (MyLocation.Location[x+i][y]==turn)
        {
            count1++;
        }
        else
        {
            break;
        }
    }
    for (int i=0; i<5; i++)
    {
        if (MyLocation.Location[x][y+i]==turn)
        {
            count2++;
        }
        else
        {
            break;
        }
    }
    for (int i=0; i<5; i++)
    {
        if (MyLocation.Location[x+i][y+i]==turn)
        {
            count3++;
        }
        else
        {
            break;
        }
    }

    //qDebug("[%d][%d]=%d", x, y, MyLocation.Location[x][y]);
    if (count1==5 || count2==5 || count3==5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*判断左斜，是否有5个连续棋子
输入：坐标和玩家， 输出1/0*/
int ChessBoard::fineFive2(int x, int y, int turn)
{
    int count4=0;
    for (int i=0; i<5; i++)
    {
        if (MyLocation.Location[x-i][y+i]==turn)
        {
            count4++;
        }
        else
        {
            break;
        }
    }
    if (count4==5)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

/*扫描所有棋盘，调用findFive判断是否有5连子
输入：当前玩家， 输出：true/false*/
bool ChessBoard::isWin(bool* player)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGH; j++)
        {
            int ret = fineFive(i, j, 2);
            if (ret == 1)
            {
                *player=true;
                return true;
            }
            ret = fineFive(i, j, 1);
            if (ret == 1)
            {
                *player=false;
                return true;
            }
        }
    }

    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGH; j++)
        {
            int ret = fineFive2(i, j, 2);
            if (ret == 1)
            {
                *player=true;
                return true;
            }
            ret = fineFive2(i, j, 1);
            if (ret == 1)
            {
                *player=false;
                return true;
            }
        }
    }
    return false;
}

/*
 * AI回合，为电脑棋子和玩家打分
 * 电脑分数高则进攻，玩家分数则防守
*/
void ChessBoard::ComputerTurn()
{
    int CompScore=0;
    int HuScore=0;
    ComputerScore.LocationClear();
    HumanScore.LocationClear();

    CompScore = HighScore(1);
    HuScore = HighScore(2);

    //HumanScore.PrintLocation();
    //qDebug("Com FindMax=%d", CompScore);
    //qDebug("Hum FindMax=%d", HuScore);
    if (CompScore >= HuScore)
    {
        ComputerAttack(CompScore);
    }
    else
    {
        ComputerDefence(HuScore);
    }
}

/*
 * 求出棋盘最高分
 * 对每一个无棋子的位置进行计算，八个方向棋子棋子数越高分数越高
 * 例如1->1,2->10,3->100,4->1000
 * 将八个方向分数相加，获得当前位置的分数，写入评分数组
 * turn=1时计算电脑分数，turn=2时计算玩家分数
*/
int ChessBoard::HighScore(int turn)
{
    int HightScore=0;

    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGH; j++)
        {
            if (MyLocation.Location[i][j]==0)
            {
                double count=0;
                double Comscore=0;
                for (int k=1; k<=4; k++)        //横右判断
                {
                    if(i+k>=WIDTH)
                        break;
                    if(MyLocation.Location[i+k][j]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                count=0;
                for (int k=1; k<=4; k++)        //横左判断
                {
                    if(i-k<0)
                        break;
                    if(MyLocation.Location[i-k][j]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                count=0;
                for (int k=1; k<=4; k++)        //竖下判断
                {
                    if(j+k>=HEIGH)
                        break;
                    if(MyLocation.Location[i][j+k]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                count=0;
                for (int k=1; k<=4; k++)        //横右判断
                {
                    if(j-k<0)
                        break;
                    if(MyLocation.Location[i][j-k]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                //后面是斜的
                count=0;
                for (int k=1; k<=4; k++)        //左上判断
                {
                    if(i-k<0 || j-k<0)
                        break;
                    if(MyLocation.Location[i-k][j-k]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                count=0;
                for (int k=1; k<=4; k++)        //右上判断
                {
                    if(i+k>=WIDTH || j-k<0)
                        break;
                    if(MyLocation.Location[i+k][j-k]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                count=0;
                for (int k=1; k<=4; k++)        //左下判断
                {
                    if(i-k<0 || j+k>=HEIGH)
                        break;
                    if(MyLocation.Location[i-k][j+k]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                count=0;
                for (int k=1; k<=4; k++)        //右下判断
                {
                    if(i+k>=WIDTH || j+k>=HEIGH)
                        break;
                    if(MyLocation.Location[i+k][j+k]==turn)
                    {
                        Comscore+=pow(10, count);
                        count++;
                    }
                }
                if (turn == 1)
                {
                    ComputerScore.Location[i][j]+=(int)Comscore;
                }
                else if (turn == 2)
                {
                    HumanScore.Location[i][j]+=(int)Comscore;
                }

            }//if

            if (turn == 1)
            {
                FindMax(&HightScore, ComputerScore.Location[i][j]);
            }
            else if (turn == 2)
            {
                FindMax(&HightScore, HumanScore.Location[i][j]);
            }
            else
            {
                qDebug("Find HighScore error");
            }
        }
    }
    return HightScore;
}

/*比较分数最大值*/
void ChessBoard::FindMax(int* Orig, int Chang)
{
    if(Chang>*Orig)
    {
        *Orig=Chang;
    }
}

/*
 * AI攻击
 * 在AI评分数组ComputerScore中，选一个最高分周围有棋子的位置落子
*/
void ChessBoard::ComputerAttack(int HighScore)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGH; j++)
        {
            if(ComputerScore.Location[i][j]==HighScore)
            {
                if (MyLocation.Location[i-1][j]>0 && i>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i+1][j]>0 && i<WIDTH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i][j-1]>0 && j>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i][j+1]>0 && j<HEIGH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                //后面是斜的
                if (MyLocation.Location[i-1][j-1]>0 && i>0 && j>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i+1][j-1]>0 && i<WIDTH-1 && j>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i-1][j+1]>0 && i>0 && j<HEIGH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i+1][j+1]>0 && i<WIDTH-1 && j<HEIGH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
            }
        }
    }//for
    PlaceHigh(HighScore);
}

/*
 * AI防御
*/
void ChessBoard::ComputerDefence(int HighScore)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGH; j++)
        {
            if(HumanScore.Location[i][j]==HighScore)
            {
                if (MyLocation.Location[i-1][j]>0 && i>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i+1][j]>0 && i<WIDTH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i][j-1]>0 && j>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i][j+1]>0 && j<HEIGH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                //后面是斜的
                if (MyLocation.Location[i-1][j-1]>0 && i>0 && j>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i+1][j-1]>0 && i<WIDTH-1 && j>0)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i-1][j+1]>0 && i>0 && j<HEIGH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
                if (MyLocation.Location[i+1][j+1]>0 && i<WIDTH-1 && j<HEIGH-1)
                {
                    MyLocation.Location[i][j]=1;
                    LocUnit.x=i;
                    LocUnit.y=j;
                    LocationStack.push(LocUnit);
                    return;
                }
            }
        }
    }//for
    PlaceHigh(HighScore);
}

/*
 * 对于最高分周围无棋子的，随便放一个位置
*/
void ChessBoard::PlaceHigh(int HighScore)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<HEIGH; j++)
        {
            if(HumanScore.Location[i][j]==HighScore)
            {
                MyLocation.Location[i][j]=1;
                LocUnit.x=i;
                LocUnit.y=j;
                LocationStack.push(LocUnit);
                return;
            }
        }
    }
}
