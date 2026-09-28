#include "Enemy.h"
#include <iostream>

Enemy::Enemy() {
    if (!texture.loadFromFile("Resourses\\enemy.png")) {
        std::cerr << "Failed to load enemy texture" << std::endl;
    }
    setTexture(texture);
    setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    scoreValue = 0;
}

void Enemy::update() {
   move(0, 0.1f); // Движение вниз
}

void Enemy::setScoreValue(int value) {
    scoreValue = value;
}

int Enemy::getScoreValue() const {
    return scoreValue;
}
