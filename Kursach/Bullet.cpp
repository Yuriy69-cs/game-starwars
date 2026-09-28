#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position) {
    if (!texture.loadFromFile("Resourses\\bullet.png")) {
        std::exception("Failed to load bullet texture");
    }
    setTexture(texture);
    setScale(0.2f, 0.2f);
    setOrigin(texture.getSize().x - 50, texture.getSize().y -10);
    setPosition(position);
}

void Bullet::update() {
    move(0, -0.5f); // Замедление движения пули вверх
}
