#include "tema/MoneyStars.h"

using namespace tema;

MoneyStars::MoneyStars(std::string newColor, float x, float y, float newSize): color(newColor), posX(x), posY(y), size(newSize) {
}

std::string MoneyStars::getColor()
{
    return color;
}

float MoneyStars::getPosX() {
    return posX;
}
float MoneyStars::getPosY() {
    return posY;
}

void MoneyStars::setPosX(float x) {
    posX = x;
}

void MoneyStars::setPosY(float y) {
    posY = y;
}

void MoneyStars::setSize(float newSize) {
    size = newSize;
}

float MoneyStars::getSize() {
    return size;
}