#ifndef TETRIXSQUARE_H
#define TETRIXSQUARE_H
#include "Entity.h"
class TetrixSquare
{
private:
    sf::Sprite sprite;
public:
    TetrixSquare(float x, float y, int size, sf::Texture &texture, int start_frame_x, int start_frame_y, int width, int height);
    virtual ~TetrixSquare();

    const sf::FloatRect getGlobalBounds();
    const sf::Vector2f getPosition();
    const sf::Vector2f getRelativePosition(const sf::Vector2f position);
    const sf::Vector2i getRelativeSquareTile(const sf::Vector2f position);

    void setPosition(const float x, const float y);

    // Functions
    void move(const float x, const float y);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};
#endif

