#include <screen.h>

void Screen::grid_init()
{
    grid_line.resize((X_COUNT + Y_COUNT + 2) * 2);
    grid_line.setPrimitiveType(sf::Lines);

    for (int x = 0; x < X_COUNT + 1; ++x)
    {
        grid_line[x * 2].position = sf::Vector2f{x * GRID_SIZE + MARGIN_LEFT, 0 + MARGIN_TOP};
        grid_line[x * 2 + 1].position = sf::Vector2f{x * GRID_SIZE + MARGIN_LEFT, Y_COUNT * GRID_SIZE + MARGIN_TOP};
    }

    for (int y = 0; y < Y_COUNT + 1; ++y)
    {
        grid_line[(X_COUNT + 1) * 2 + y * 2].position = sf::Vector2f{0 + MARGIN_LEFT, y * GRID_SIZE + MARGIN_TOP};
        grid_line[(X_COUNT + 1) * 2 + y * 2 + 1].position = sf::Vector2f{X_COUNT * GRID_SIZE + MARGIN_LEFT, y * GRID_SIZE + MARGIN_TOP};
    }
}

void Screen::init()
{
    blocks.resize(X_COUNT * Y_COUNT * 6);
    blocks.setPrimitiveType(sf::Triangles);
    for (int x = 0; x < X_COUNT; ++x)
    {
        for (int y = 0; y < Y_COUNT; ++y)
        {
            auto index = (y * X_COUNT + x) * 6;
            sf::Vector2f coord2d(x * GRID_SIZE + MARGIN_LEFT, y * GRID_SIZE + MARGIN_TOP);

            blocks[index].position = coord2d;
            blocks[index].color = sf::Color::Blue;

            blocks[index + 1].position = coord2d + sf::Vector2f{GRID_SIZE, 0};
            blocks[index + 1].color = sf::Color::Blue;

            blocks[index + 2].position = coord2d + sf::Vector2f{GRID_SIZE, GRID_SIZE};
            blocks[index + 2].color = sf::Color::Blue;

            blocks[index + 3].position = coord2d + sf::Vector2f{GRID_SIZE, GRID_SIZE};
            blocks[index + 3].color = sf::Color::Blue;

            blocks[index + 4].position = coord2d + sf::Vector2f{0, GRID_SIZE};
            blocks[index + 4].color = sf::Color::Blue;

            blocks[index + 5].position = coord2d;
            blocks[index + 5].color = sf::Color::Blue;
        }
    }

    grid_init();
}

void Screen::update(int x, int y, sf::Color color)
{
    auto index = (y * X_COUNT + x) * 6;

    blocks[index].color = color;
    blocks[index + 1].color = color;
    blocks[index + 2].color = color;
    blocks[index + 3].color = color;
    blocks[index + 4].color = color;
    blocks[index + 5].color = color;
}

void Screen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(blocks);
    target.draw(grid_line);
}

void Screen::render_tetrominoes(Tetrominoes *tetrominoes)
{
    for (auto shape : tetrominoes->m_shape)
    {
        if (shape[1] < 0)
        {
            continue;
        }
        update(shape[0], shape[1], sf::Color::Green);
    }
}