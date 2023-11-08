#pragma once
#include "components/simple_scene.h"
	class Weapon : public Mesh
	{


	public:
		glm::mat3 getDiamondMatrix();
		void setDiamondMatrix(glm::mat3 newMatrix);
		glm::mat3 getSquareMatrix();
		void setSquareMatrix(glm::mat3 newMatrix);

	protected:
		glm::mat3 diamondMatrix;
		glm::mat3 squareMatrix;
	};

