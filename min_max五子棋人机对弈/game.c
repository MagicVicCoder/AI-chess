#include "game.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void init(Game* pthis, int w, int h) {
    srand(time(NULL));
    initgraph(w, h, EX_SHOWCONSOLE);
    pthis->isRunning = true;
    pthis->row = -1;
    pthis->col = -1;
    pthis->currentChessType = White;   // 默认白棋先下（可根据需要调整）
    memset(pthis->map, 0, sizeof(int) * ROWS * COLS);
    pthis->currentchess_row = pthis->currentchess_col = -1;
    pthis->player = human;              // 默认人先手
    pthis->specialRow = pthis->specialCol = -1;
    pthis->is_warning = false;
}

void render(Game* pthis) {
    // 绘制所有棋子
    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLS; k++) {
            if (pthis->map[i][k] != None) {
                int x = k * GRID_SIZE + XOFFSET;
                int y = i * GRID_SIZE + YOFFSET;
                if (pthis->map[i][k] == White) {
                    setfillcolor(WHITE);
                } else if (pthis->map[i][k] == Black) {
                    setfillcolor(BLACK);
                }
                solidcircle(x, y, 20);
            }
        }
    }
    // 绘制鼠标所在格子的提示框
    if (pthis->row != -1 && pthis->col != -1) {
        setlinecolor(BLUE);
        int x = pthis->col * GRID_SIZE + XOFFSET;
        int y = pthis->row * GRID_SIZE + YOFFSET;
        circle(x, y, 25);
    }
}

void update(Game* pthis) {
    // 鼠标移动：更新当前格子
    if (pthis->msg.message == WM_MOUSEMOVE) {
        for (int i = 0; i < ROWS; i++) {
            for (int k = 0; k < COLS; k++) {
                int cx = k * GRID_SIZE + XOFFSET;
                int cy = i * GRID_SIZE + YOFFSET;
                if (abs(pthis->msg.x - cx) < GRID_SIZE / 2 && abs(pthis->msg.y - cy) < GRID_SIZE / 2) {
                    pthis->row = i;
                    pthis->col = k;
                    goto END_LOOP;
                }
            }
        }
        END_LOOP:;
    }
    // 鼠标左键点击：下棋
    else if (pthis->msg.message == WM_LBUTTONDOWN && 
             pthis->row != -1 && pthis->col != -1 && 
             pthis->map[pthis->row][pthis->col] == None) {
        pthis->map[pthis->row][pthis->col] = pthis->currentChessType;
        pthis->currentchess_row = pthis->row;
        pthis->currentchess_col = pthis->col;
        pthis->currentChessType = (ChessType)-pthis->currentChessType; // 切换棋子颜色
        shiftplayer(pthis); // 切换人机状态
    }
}

void creatUI(Game* pthis, IMAGE* theimage) {
    BeginBatchDraw();
    cleardevice();
    putimage(0, 0, theimage);
    render(pthis);
    EndBatchDraw();
}

void shiftplayer(Game* pthis) {
    if (pthis->player == human) {
        pthis->player = robot;
    } else if (pthis->player == robot) {
        pthis->player = human;
    }
}