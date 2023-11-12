#pragma once
#include "tema/Weapon.h"

using namespace tema;

Weapon::Weapon(int newId, std::string newColor, float x, float y, float newSize, float newRadius) : id(newId), color(newColor), posX(x), posY(y), size(newSize), radius(newRadius) {
}

std::string Weapon::getColor()
{
    return color;
}

int Weapon::getId() {
    return id;
}

float Weapon::getPosX() {
    return posX;
}
float Weapon::getPosY() {
    return posY;
}

void Weapon::setPosX(float x) {
    posX = x;
}

void Weapon::setPosY(float y) {
    posY = y;
}

void Weapon::setSize(float newSize) {
    size = newSize;
}

float Weapon::getSize() {
    return size;
}

void Weapon::setRadius(float newRadius) {
    radius = newRadius;
}

float Weapon::getRadius() {
    return radius;
}

//void setElapsedTime(std::chrono::seconds time);
//std::chrono::seconds getElapsedTime();
//void setCurrentTime(std::chrono::time_point<std::chrono::high_resolution_clock> time);
//std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime();
//void setLastUpdateTime(std::chrono::time_point<std::chrono::high_resolution_clock> time);
//std::chrono::time_point<std::chrono::high_resolution_clock> getLastUpdateTime();