#ifndef JUDGE_H
#define JUDGE_H

#include "game.h"

// 检查在(row,col)放置color棋子后，是否形成num子连珠
bool check_win_at(Game* pthis, int row, int col, ChessType color, int num);
// 检查最后一次落子是否导致游戏结束（达到num子）
bool check_game_over(Game* pthis, int num);

#endif