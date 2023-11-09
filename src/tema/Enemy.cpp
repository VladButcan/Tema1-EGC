#include "tema/Enemy.h"

using namespace tema;

Enemy::Enemy(int newId, std::string newColor, float x, float y): id(newId), color(newColor), posX(x), posY(y) {
    if (color == "orangeHexagon") {
        healt = 3;
    } else {
        if (color == "blueHexagon") {
            healt = 4;
        } else {
            if (color == "yellowHexagon") {
                healt = 5;
            } else {
                    healt = 6;
            }
        }
    }
}

std::string Enemy::getColor()
{
    return color;
}

int Enemy::getId() {
    return id; 
}

int Enemy::getHealt() {
    return healt; 
}

void Enemy::setHealt(int newHealt) {
    healt = newHealt;
}
float Enemy::getPosX() {
    return posX;
}
float Enemy::getPosY() {
    return posY;
}

void Enemy::setPosX(float x) {
    posX = x;
}

void Enemy::setPosY(float y) {
    posY = y;
}