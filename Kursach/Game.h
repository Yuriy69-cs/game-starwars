#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void spawnEnemy();
    void drawScore();
    void drawGameOver();

    sf::RenderWindow window;
    Player player;
    Enemy Enemys;
    Bullet Bullets;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    int score;
    sf::Font font;
    sf::Text scoreText;
    sf::Text retryText;
    sf::Text endText;
    sf::Clock enemySpawnClock;
    float enemySpawnInterval;
    int comboCount; // —чЄтчик серийных убийств
    sf::SoundBuffer shootBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::Sound shootSound;
    sf::Sound explosionSound;
    bool gameOver;
};

#endif // GAME_H
