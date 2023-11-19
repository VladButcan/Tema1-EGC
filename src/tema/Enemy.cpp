#include "tema/Enemy.h"

using namespace tema;

Enemy::Enemy(std::string newColor, float x, float y, float newSize)
      : color(newColor), posX(x), posY(y), size(newSize) {
    if (color == "orange") {
        healt = 10;
    } else {
        if (color == "blue") {
            healt = 20;
        } else {
            if (color == "yellow") {
                healt = 30;
            } else {
                    healt = 40;
            }
        }
    }
    radius = 5.0f;
    speed = 1;
}

std::string Enemy::getColor()
{
    return color;
}

void Enemy::setHealt(int newHealt) {
    healt = newHealt;
}

int Enemy::getHealt() {
    return healt;
}

void Enemy::setPosX(float x) {
    posX = x;
}

float Enemy::getPosX() {
    return posX;
}

void Enemy::setPosY(float y) {
    posY = y;
}

float Enemy::getPosY() {
    return posY;
}

void Enemy::setSize(float newSize) {
    size = newSize;
}

float Enemy::getSize() {
    return size;
}

void Enemy::setRadius(float newRadius) {
    radius = newRadius;
}

float Enemy::getRadius() {
    return radius;
}

void Enemy::setSpeed(int newSPeed) {
    speed = newSPeed;
}

int Enemy::getSpeed() {
    return speed;
}