#include "tema/Enemy.h"

using namespace tema;

Enemy::Enemy(int id, std::string color) {
    this.id = id;
    this.color = color;
    switch (color) {
        case "orangeHexagon":
            this.healt = 3;
        case "blueHexagon":
            this.healt = 4;
        case "yellowHexagon":
            this.healt = 5;
        case "purpleHexagon":
            this.healt = 6;
    }
}

std::string Enemy::getColor()
{
    return this.color;
}

int Enemy::getId() {
    return this.id; 
}

int Enemy::getHealt() {
    return this.healt; 
}

void Enemy::setHealt(int healt) {
    this.healt = healt;
}