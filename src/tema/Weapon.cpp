#include "Weapon.h"
#include <vector>
#include <iostream>


glm::mat3 Weapon::getDiamondMatrix() {
	return diamondMatrix;
}

void Weapon::setDiamondMatrix(glm::mat3 newMatrix) {
	diamondMatrix = newMatrix;
}

glm::mat3 Weapon::getSquareMatrix() {
	return squareMatrix;
}

void Weapon::setSquareMatrix(glm::mat3 newMatrix) {
	squareMatrix = newMatrix;
}
