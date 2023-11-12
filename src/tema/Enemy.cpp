#include "tema/Enemy.h"

using namespace tema;

Enemy::Enemy(int newId, std::string newColor, float x, float y, float newSize, glm::mat3 newModelMatrix): id(newId), color(newColor), posX(x), posY(y), size(newSize), modelMatrix(newModelMatrix) {
    if (color == "orange") {
        healt = 3;
    } else {
        if (color == "blue") {
            healt = 4;
        } else {
            if (color == "yellow") {
                healt = 5;
            } else {
                    healt = 6;
            }
        }
    }
    radius = 5.0f;
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

void Enemy::translateMatrix(float x, float y) {
    modelMatrix *= transform2D::Translate(x, y);
}

void Enemy::scaleMatrix(float x, float y) {
    modelMatrix *= transform2D::Scale(x, y);
}

glm::mat3 Enemy::getMatrix() {
    return modelMatrix;
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