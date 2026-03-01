#include "judge.h"

bool check_win_at(Game* pthis, int row, int col, ChessType color, int num) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return false;
    if (pthis->map[row][col] != color) return false;

    int dirs[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} }; // 四个方向：竖、横、主对角、副对角
    for (int d = 0; d < 4; d++) {
        int count = 1; // 当前棋子
        // 正方向延伸
        for (int step = 1; step < num; step++) {
            int nr = row + dirs[d][0] * step;
            int nc = col + dirs[d][1] * step;
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) break;
            if (pthis->map[nr][nc] == color) count++;
            else break;
        }
        // 反方向延伸
        for (int step = 1; step < num; step++) {
            int nr = row - dirs[d][0] * step;
            int nc = col - dirs[d][1] * step;
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) break;
            if (pthis->map[nr][nc] == color) count++;
            else break;
        }
        if (count >= num) return true;
    }
    return false;
}

bool check_game_over(Game* pthis, int num) {
    if (pthis->currentchess_row < 0 || pthis->currentchess_col < 0) return false;
    ChessType last = (ChessType)pthis->map[pthis->currentchess_row][pthis->currentchess_col];
    if (last == None) return false;
    return check_win_at(pthis, pthis->currentchess_row, pthis->currentchess_col, last, num);
}