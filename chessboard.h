#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QFrame>
#include <stack>
#include "chesslocation.h"

using namespace std;


class ChessBoard : public QFrame
{
    Q_OBJECT
public:
    ChessBoard(QWidget *parent);
    ChessLocation MyLocation;
    ChessLocation ComputerScore;
    ChessLocation HumanScore;
    bool isWin(bool* player);
    int fineFive(int x, int y, int turn);
    int fineFive2(int x, int y, int turn);
    void ComputerTurn();
    int HighScore(int turn);
    void FindMax(int* Orig, int Chang);
    void ComputerAttack(int HighScore);
    void ComputerDefence(int HighScore);
    void PlaceHigh(int HighScore);

    typedef struct LocCorr
    {
        int x;
        int y;
    }Loc;
    Loc LocUnit;
    stack<Loc> LocationStack;

private:
    void paintEvent(QPaintEvent * event);


};

#endif // CHESSBOARD_H
