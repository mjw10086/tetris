#ifndef __SCREEN_H_
#define __SCREEN_H_

#include <SFML/Graphics.hpp>
#include <tetrominoes.h>
#include <consts.h>

class Screen : public sf::Drawable
{
private:
    sf::VertexArray grid_line;
    sf::VertexArray blocks;
    int m_x_count;
    int m_y_count;
    float m_grid_size;
    float m_margin[4];

private:
    void grid_init();

public:
    void init();
    void update(int x, int y, sf::Color color);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void render_tetrominoes(Tetrominoes *tetrominoes);
};

#endif