#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Сбей самолетик"), score(0), enemySpawnInterval(2.0f), comboCount(0), Bullets(sf::Vector2f(1.f, 1.f)) {
    // Инициализация игрока
    player.setPosition(400, 500);

    // Инициализация врагов
    for (int i = 0; i < 5; ++i) {
        spawnEnemy();
    }

    // Инициализация шрифта и текста очков
    if (!font.loadFromFile("Resourses\\arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x - scoreText.getLocalBounds().width, 0);

    // Инициализация текста "Retry"
    retryText.setFont(font);
    retryText.setCharacterSize(36);
    retryText.setFillColor(sf::Color::Red);
    retryText.setString("Retry");
    retryText.setPosition(window.getSize().x / 2 - retryText.getLocalBounds().width / 2, window.getSize().y / 2 - retryText.getLocalBounds().height / 2 - 50);

    // Инициализация текста "End"
    endText.setFont(font);
    endText.setCharacterSize(36);
    endText.setFillColor(sf::Color::Red);
    endText.setString("End");
    endText.setPosition(window.getSize().x / 2 - endText.getLocalBounds().width / 2, window.getSize().y / 2 - endText.getLocalBounds().height / 2 + 50);


    // Инициализация звуковых эффектов
    if (!shootBuffer.loadFromFile("Resourses\\shoot.wav")) {
        std::cerr << "Failed to load shoot sound" << std::endl;
    }
    if (!explosionBuffer.loadFromFile("Resourses\\explosion.wav")) {
        std::cerr << "Failed to load explosion sound" << std::endl;
    }
    shootSound.setBuffer(shootBuffer);
    explosionSound.setBuffer(explosionBuffer);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (!gameOver) {
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl) {
                player.shoot(bullets);
                shootSound.play();
            }
            if (gameOver && (event.key.code == sf::Keyboard::R)) {
                // Перезапуск игры
                score = 0;
                comboCount = 0;
                enemies.clear();
                bullets.clear();
                player.setPosition(400, 500);
                for (int i = 0; i < 5; ++i) {
                    spawnEnemy();
                }
                gameOver = false;
            }
            if (gameOver && (event.key.code == sf::Keyboard::E)) {
                // Завершение игры
                window.close();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (gameOver) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (retryText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Перезапуск игры
                    score = 0;
                    comboCount = 0;
                    enemies.clear();
                    bullets.clear();
                    player.setPosition(400, 500);
                    for (int i = 0; i < 5; ++i) {
                        spawnEnemy();
                    }
                    gameOver = false;
                }
                if (endText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Завершение игры
                    window.close();
                }
            }
        }
    }
}

void Game::update() {
    player.update();
    for (auto& enemy : enemies) {
        enemy.update();
    }
    for (auto& bullet : bullets) {
        bullet.update();
    }
    // Удаление пуль, которые вышли за пределы экрана
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
        return bullet.getPosition().y < 0;
        }), bullets.end());


    // Удаление врагов, которые вышли за пределы экрана
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
        return enemy.getPosition().x < -50;
        }), enemies.end());
    bool eraseBullet = false;
    // Проверка столкновений пуль с врагами
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        eraseBullet = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (it->getGlobalBounds().intersects(enemyIt->getGlobalBounds())) {
                score += enemyIt->getScoreValue() * (comboCount + 1);
                comboCount++;
                enemyIt = enemies.erase(enemyIt);
                eraseBullet = true;
                explosionSound.play();
                break;
            }
            else {
                ++enemyIt;
            }
        }
        if (eraseBullet) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }

    // Если все пули прошли мимо врагов, сбрасываем счетчик серий
    if (bullets.size() > 0 && !eraseBullet) {
        comboCount = 0; // Серия прервана
    }

    // Спавн новых врагов
    if (enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnInterval) {
        spawnEnemy();
        enemySpawnClock.restart();
    }
    //столкновение игрока с врагами
    for (const auto& enemy : enemies) {
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            std::cout << "Game Over!" << std::endl;
            gameOver = true; // Установка флага gameOver
            break;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(window.getSize().x - scoreText.getLocalBounds().width, 0);//обновление очков
}

void Game::render() {
    window.clear(sf::Color::Blue);
    window.draw(player);


    for (Enemy enemy : enemies) {
        Enemys.setPosition(enemy.getPosition());
        window.draw(Enemys);
    }

    for (const auto& bullet : bullets) {
        Bullets.setPosition(bullet.getPosition());
        window.draw(Bullets);
    }
    drawScore();
    if (gameOver) {
        drawGameOver();
    }
    window.display();
}

void Game::spawnEnemy() {
    Enemy enemy;
    enemy.setPosition(rand() % 1000 + 10, -10); // Появление врагов
    enemy.setScoreValue(rand() % 10 + 10); // Случайное значение от 10 до 20 очков
    enemies.push_back(enemy);
}

void Game::drawScore() {
    window.draw(scoreText);
}
void Game::drawGameOver() {

    window.draw(retryText);
    window.draw(endText);
}