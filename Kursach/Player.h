#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player : public sf::Sprite {
public:
    Player();
    void update();
    void shoot(std::vector<Bullet>& bullets);

private:
    sf::Texture texture;
};

#endif // PLAYER_H
