五子棋

1. 简介
使用QT实现单人与AI对战五子棋。QT打开wuzi.pro文件打开项目，编译并运行。玩家先落子，然后AI落子，任意一方有五连子时胜利。
胜利时，弹出胜利窗口，按“再来一次”重置棋盘。按“退出”退出游戏。
右侧“重置”按钮重置棋盘，“悔棋”按钮回退AI和玩家上一步操作。

2. 程序结构
Mainwindow.h:	主窗口
	鼠标事件，控件布局。
	判断胜利，并调用胜利了界面。
	棋盘重置，悔棋。
Chessboard.h: 	绘图窗口
	棋盘数组，AI评分数组，玩家评分数组
	绘图事件。
	判断是否胜利函数。
	AI回合，对AI棋子和玩家棋子打分，判断AI落子位置。
Chesslocation.h: 棋盘数组 
	棋盘数组，初始化，清空，测试打印
Winning.h: 胜利窗口
	由主窗口调用，显示胜利信息，判断重置棋盘或退出程序

3. 算法
棋盘：	棋盘由二维数组构成，窗口坐标与数组位置对应。
	鼠标点击时记录当前坐标，并对应到数组中。
	AI在棋盘数组值为1，玩家为2。
胜负：	循环遍历整个数组，向右，下，右下，左下判断是否有五连子。
	（未解决数组越界）
AI：	AI回合时，循环遍历所有未落子的点，计算八个方向，有几个子。
	某一方向如果有1个子，计分为1。2个子为10。3个子为100。4个子为1000。
	分别对AI和玩家棋子进行打分，对比，如果AI分数高则进攻，玩家分数高则防守。
	AI落子时，循环所有最高分的位置，如果边上有子则落在当前位置，没有则随机落一个位置。
悔棋：	AI和玩家落子时将数组位置入栈，悔棋时出栈。
	栈的类型为结构体，包含x和y的坐标。