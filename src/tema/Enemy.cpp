#include "tema/Enemy.h"

using namespace tema;

Enemy::Enemy(int newId, std::string newColor, float x, float y, float newSize): id(newId), color(newColor), posX(x), posY(y), size(newSize) {
    if (color == "orange") {
        healt = 2.0f;
    } else {
        if (color == "blue") {
            healt = 3.0f;
        } else {
            if (color == "yellow") {
                healt = 4.0f;
            } else {
                    healt = 5.0f;
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

int Enemy::getId() {
    return id; 
}

void Enemy::setHealt(int newHealt) {
    healt = newHealt;
}

float Enemy::getHealt() {
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

void Enemy::setSpeed(float newSPeed) {
    speed = newSPeed;
}

float Enemy::getSpeed() {
    return speed;
}