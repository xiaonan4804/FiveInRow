#include "chesslocation.h"
#include <QDebug>

ChessLocation::ChessLocation()
{
    for (int i=0; i<this->width; i++)
    {
        for (int j=0; j<this->height; j++)
        {
            Location[i][j] = 0;
        }
    }

}

/*
 * 清空数组
*/
void ChessLocation::LocationClear()
{
    for (int i=0; i<this->width; i++)
    {
        for (int j=0; j<this->height; j++)
        {
            Location[i][j] = 0;
        }
    }
}

/*
 * 在终端打印数组，用于测试
*/
void ChessLocation::PrintLocation()
{
    for (int j=0; j<this->height; j++)
    {
        qDebug("%-4d  %-4d  %-4d  %-4d  %-4d  %-4d  %-4d  %-4d  %-4d  %-4d",
               Location[0][j],Location[1][j],Location[2][j],Location[3][j],Location[4][j],
                Location[5][j],Location[6][j],Location[7][j],Location[8][j],Location[9][j]);
    }

}
