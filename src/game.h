#ifndef __GAME_H_
#define __GAME_H_

#include <tetrominoes.h>
#include <screen.h>
#include <SFML/Graphics.hpp>
#include <consts.h>

enum GAMESTATUS
{
    RUN,
    PUASE,
    GAMEOVER,
};

const int SPEED = 30;

class Game
{
private:
    int m_matrix[Y_COUNT][X_COUNT] = {0};
    Tetrominoes *m_tetrominoes;
    Screen screen;
    GAMESTATUS status = RUN;
    int score = 0;
    int frame_per_sec = 120;
    int speed = SPEED; // 每自动下落一格所占用一秒总帧数
    int frame_count = 0;
    int manual_drop_speed = 60;

    sf::RenderWindow window;

private:
    void
    update_screen();
    void step();
    bool drop_impack_check();
    bool overlap_impack_check();
    void update_tetrominoes_to_matrix();
    bool line_clear();
    void line_full_flicker(bool full_row[Y_COUNT]);

public:
    Game();
    void run();
    static TETROMINOES_TYPE get_rand_type();
};

#endif