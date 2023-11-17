#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateSquare(const std::string &name, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 color, bool fill = false);
    Mesh* CreateWeapon(const std::string& name, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 color, bool fill = false);
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
}
