#pragma once
#include "tema/Heart.h"

using namespace tema;

Heart::Heart(std::string newColor, float newCenterLeftCircle, float newCenterRightCircle, float newRadius) : color(newColor), centerLeftCircle(newCenterLeftCircle), centerRightCircle(newCenterRightCircle), radius(newRadius) {
}

//std::string Heart::getColor()
//{
//    return color;
//}
//
//int Heart::getId() {
//    return id;
//}
//
//float Heart::getPosX() {
//    return posX;
//}
//float Heart::getPosY() {
//    return posY;
//}
//
//void Heart::setPosX(float x) {
//    posX = x;
//}
//
//void Heart::setPosY(float y) {
//    posY = y;
//}
//
//void Heart::setSize(float newSize) {
//    size = newSize;
//}
//
//float Heart::getSize() {
//    return size;
//}