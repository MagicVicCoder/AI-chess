#ifndef AI_H
#define AI_H

#include "game.h"

typedef struct {
    int x;
    int y;
} Coordinate;

// 判断(x,y)是否可作为候选落子点（邻居空位）
bool isNextchess(State* state, int x, int y, int n);
// 评估棋局分数（相对于当前执棋方）
int score(State* state, ChessType a);
// 获取最佳落子坐标
Coordinate get_best_move(Game* pthis, State* state, int depth);
// 机器走一步棋
void robotplay(Game* pthis);
// 计算机器落子坐标（调用get_best_move）
void figure_coord(Game* pthis);

// 内部评分函数（供AI使用）
Count detect_succession(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]);
int countPoint(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]);

#endif