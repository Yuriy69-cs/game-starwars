#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
    Bullet(const sf::Vector2f& position);
    void update();

private:
    sf::Texture texture;
};

#endif // BULLET_H
