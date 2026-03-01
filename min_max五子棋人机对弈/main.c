#include "game.h"
#include "ai.h"
#include "judge.h"
#include <windows.h> // for MessageBox

int main() {
    Game game;
    init(&game, 1000, 1000);
    IMAGE img_bg;
    // 背景图片路径
    loadimage(&img_bg, L"Board.jpg");
    putimage(0, 0, &img_bg);

    while (game.isRunning) {
        // 检查是否五子连珠（游戏结束）
        if (check_game_over(&game, 5)) {
            MessageBox(GetHWnd(), L"游戏结束", L"提示", MB_OK);
            game.isRunning = false;
            break;
        }

        if (game.player == human) {
            if (peekmessage(&game.msg)) {
                update(&game);
            }
            creatUI(&game, &img_bg);
        } else if (game.player == robot) {
            robotplay(&game);
            creatUI(&game, &img_bg);
            shiftplayer(&game); // 切换回人类
        }
    }
    return 0;
}