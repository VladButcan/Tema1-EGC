#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 color, bool fill = false);
    //Mesh* CreateTransparentSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec4 color);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateWeapon(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, float centerX, float centerY, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateHeart(const std::string& name, glm::vec3 color, bool fill = false);
    Mesh* CreateZero(const std::string& name, glm::vec3 color);
    Mesh* CreateOne(const std::string& name, glm::vec3 color);
    Mesh* CreateTwo(const std::string& name, glm::vec3 color);
    Mesh* CreateThree(const std::string& name, glm::vec3 color);
    Mesh* CreateFour(const std::string& name, glm::vec3 color);
    Mesh* CreateFive(const std::string& name, glm::vec3 color);
    Mesh* CreateSix(const std::string& name, glm::vec3 color);
    Mesh* CreateSeven(const std::string& name, glm::vec3 color);
    Mesh* CreateEight(const std::string& name, glm::vec3 color);
    Mesh* CreateNine(const std::string& name, glm::vec3 color);
    Mesh* CreateTextDMG(const std::string& name, glm::vec3 color);
    Mesh* CreateTextSPEED(const std::string& name, glm::vec3 color);
    //void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
}
