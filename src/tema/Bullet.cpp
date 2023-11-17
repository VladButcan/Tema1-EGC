#include "tema/Bullet.h"

using namespace tema;

Bullet::Bullet(std::string newColor, float x, float y, float newSize, float newAngle)
       : color(newColor), posX(x), posY(y), size(newSize), angle(newAngle) {
    damage = 10;
    speed = 50;
    radius = 4.0f;
}

std::string Bullet::getColor()
{
    return color;
}

void Bullet::setPosX(float x) {
    posX = x;
}

float Bullet::getPosX() {
    return posX;
}

void Bullet::setPosY(float y) {
    posY = y;
}

float Bullet::getPosY() {
    return posY;
}

void Bullet::setSize(float newSize) {
    size = newSize;
}

float Bullet::getSize() {
    return size;
}

void Bullet::setAngle(float newAngle) {
    angle = newAngle;
}

float Bullet::getAngle() {
    return angle;
}

void Bullet::setRadius(float newRadius) {
    radius = newRadius;
}

float Bullet::getRadius() {
    return radius;
}