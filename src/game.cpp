#include <game.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SEC 1000000

Game::Game() : m_tetrominoes(Tetrominoes::create(Game::get_rand_type()))
{
    screen.init();
}

void Game::update_screen()
{
    for (int y = 0; y < Y_COUNT; ++y)
    {
        for (int x = 0; x < X_COUNT; ++x)
        {
            if (m_matrix[y][x])
            {
                screen.update(x, y, sf::Color::Green);
            }
            else
            {
                screen.update(x, y, sf::Color::Blue);
            }
        }
    }
}

void Game::run()
{
    window.create(sf::VideoMode(X_COUNT * GRID_SIZE + MARGIN_LEFT + MARGIN_RIGHT,
                                Y_COUNT * GRID_SIZE + MARGIN_TOP + MARGIN_BOTTOM, 1),
                  "Have Fun!", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    m_tetrominoes->filp();
                    if (overlap_impack_check())
                    {
                        m_tetrominoes->undo_filp();
                    }
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    m_tetrominoes->move(LEFT);
                    if (overlap_impack_check())
                    {
                        m_tetrominoes->move(RIGHT);
                    }
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    m_tetrominoes->move(RIGHT);
                    if (overlap_impack_check())
                    {
                        m_tetrominoes->move(LEFT);
                    }
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    speed = 1;
                }

                update_screen();
                screen.render_tetrominoes(m_tetrominoes);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    speed = SPEED;
                }
            }
        }
        if (status == RUN)
            if (frame_count == speed)
            {
                step();
            }

        window.draw(screen);
        window.display();
        usleep(SEC / frame_per_sec); // 大约120帧每秒
        frame_count++;
        if (frame_count > speed)
        {
            frame_count = 0;
        }
    }
}

void Game::step()
{
    update_screen();
    screen.render_tetrominoes(m_tetrominoes);
    if (drop_impack_check())
    {
        update_tetrominoes_to_matrix();
        if (line_clear())
        {
            update_screen();
        }
        if (drop_impack_check())
        {
            std::cout << "GAME OVER" << std::endl;
            status = GAMEOVER;
        }
    }
    m_tetrominoes->drop();
}

bool Game::drop_impack_check()
{
    for (auto shape : m_tetrominoes->m_shape)
    {
        auto y = shape[1];
        auto x = shape[0];
        if (y < -1)
            continue;

        if (m_matrix[y + 1][x] || y == Y_COUNT)
        {
            return true;
        }
    }
    return false;
}

// 重叠检测，附加越界检测
bool Game::overlap_impack_check()
{
    for (auto shape : m_tetrominoes->m_shape)
    {
        auto y = shape[1];
        auto x = shape[0];
        if (y < 0)
            continue;

        if (x < 0 || x > X_COUNT - 1)
        {
            return true;
        }

        if (m_matrix[y][x])
        {
            return true;
        }
    }
    return false;
}

void Game::update_tetrominoes_to_matrix()
{
    for (auto shape : m_tetrominoes->m_shape)
    {
        if (shape[1] < 0)
            continue;
        m_matrix[shape[1]][shape[0]] = 1;
    }
    m_tetrominoes = Tetrominoes::create(Game::get_rand_type());
}

TETROMINOES_TYPE Game::get_rand_type()
{
    srand((unsigned)time(NULL));
    return static_cast<TETROMINOES_TYPE>(rand() % 7);
}

bool Game::line_clear()
{
    bool ret = false;
    bool full_row[Y_COUNT];
    for (int y = 0; y < Y_COUNT; ++y)
    {
        full_row[y] = true;
        for (int x = 0; x < X_COUNT; ++x)
        {
            if (!m_matrix[y][x])
                full_row[y] = false;
        }
        if (full_row[y])
            ret = true;
    }

    if (ret)
    {
        line_full_flicker(full_row);
    }

    int empty_line = 0;
    for (int y = Y_COUNT - 1; y >= 0; --y)
    {
        if (full_row[y])
            empty_line += 1;

        if (empty_line != 0)
        {
            while (y - empty_line >= 0 && full_row[y - empty_line])
            {
                empty_line += 1;
            }

            for (int x = 0; x < X_COUNT; ++x)
            {
                if (y - empty_line >= 0)
                {
                    m_matrix[y][x] = m_matrix[y - empty_line][x];
                    m_matrix[y - empty_line][x] = 0;
                }
                else
                {
                    m_matrix[y][x] = 0;
                }
            }
        }
    }

    return ret;
}

void Game::line_full_flicker(bool full_row[Y_COUNT])
{
    bool even = true;
    int flicker_frequency = 3;
    for (int i = 0; i < flicker_frequency; i++)
    {
        for (int y = 0; y < Y_COUNT; y++)
        {
            if (full_row[y])
            {
                for (int x = 0; x < X_COUNT; x++)
                {
                    screen.update(x, y, even ? sf::Color::Blue : sf::Color::Green);
                }
            }
        }
        usleep(SEC * 0.5 / flicker_frequency);

        even = !even;
        window.draw(screen);
        window.display();
    }
}