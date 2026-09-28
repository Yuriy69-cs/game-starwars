#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy : public sf::Sprite {
public:
    Enemy();
    void update();
    void setScoreValue(int value);
    int getScoreValue() const;

private:
    int scoreValue;
    sf::Texture texture;
};

#endif // ENEMY_H
