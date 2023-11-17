#pragma once
#include "tema/Heart.h"

using namespace tema;

Heart::Heart(std::string newColor, float newPosX, float newPosY, float newSize) : color(newColor), posX(newPosX), posY(newPosY), size(newSize) {
}

std::string Heart::getColor()
{
    return color;
}

float Heart::getPosX() {
    return posX;
}
float Heart::getPosY() {
    return posY;
}

void Heart::setPosX(float x) {
    posX = x;
}

void Heart::setPosY(float y) {
    posY = y;
}

void Heart::setSize(float newSize) {
    size = newSize;
}

float Heart::getSize() {
    return size;
}