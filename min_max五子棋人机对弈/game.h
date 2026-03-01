#ifndef GAME_H
#define GAME_H

#include <easyx.h>
#include <stdbool.h>

#define ROWS 15
#define COLS 15
#define GRID_SIZE 65
#define XOFFSET 40
#define YOFFSET 40

enum ChessType {
    None = 0,
    Black = 1,
    White = -1
};

enum Player {
    robot = -1,
    human = 1,
};

// 方向映射（用于评分）
typedef struct DirectionMap {
    int horizontal;
    int vertical;
    int leftOblique;
    int rightOblique;
} DirectionMap;

// 计数结构（用于评分）
typedef struct Count {
    int NumOf_2Dif[5];
    int NumOf_1Dif[5];
    int NumOf_0dif[5];
    int NumOf_0jump[5];
    int NumOf_1jump[5];
    int NumOf_2jump[5];
    int NumOf_warning;
} Count;

// 棋局状态（用于AI搜索）
typedef struct State {
    int board[ROWS][COLS];
    int val;
    ChessType chesstype;
    int x, y;
    struct State* prev;
} State;

// 游戏主结构
typedef struct Game {
    int map[ROWS][COLS];
    bool isRunning;
    ExMessage msg;
    int row, col;               // 鼠标当前位置
    int currentchess_row, currentchess_col; // 最后一次落子位置
    ChessType currentChessType;  // 当前该谁下
    Player player;               // 当前操作者是人还是机器
    int robotRow, robotCol;      // 机器即将落子的坐标
    int specialRow, specialCol;  // 特殊位置（用于AI快速堵截）
    bool is_warning;
} Game;

// 游戏初始化
void init(Game* pthis, int w, int h);
// 绘制棋盘和棋子
void render(Game* pthis);
// 处理鼠标输入
void update(Game* pthis);
// 创建并刷新界面
void creatUI(Game* pthis, IMAGE* theimage);
// 切换玩家（人机交替）
void shiftplayer(Game* pthis);

#endif