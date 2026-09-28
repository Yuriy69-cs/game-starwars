#include "Player.h"
#include <iostream>

Player::Player() {
    if (!texture.loadFromFile("Resourses\\player.png")) {
        std::cerr << "Failed to load player texture" << std::endl;
    }
    setTexture(texture);
    setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(-0.2f, 0); // Замедление перемещения
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(0.2f, 0); // Замедление перемещения
    }
}

void Player::shoot(std::vector<Bullet>& bullets) {
    Bullet bullet(getPosition());
    bullets.push_back(bullet);
}
