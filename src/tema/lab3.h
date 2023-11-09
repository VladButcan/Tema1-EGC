#pragma once

#include "components/simple_scene.h"
#include <random>
#include "Enemy.h"
#include <chrono>


namespace tema
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void InitSquares();
        void InitWeapons();
        void InitStars();
        void InitHexagons();
        void RenderArena();
        void RenderHealt();
        void RenderWeapons();
        void RenderStar(int translateX, int translateY);
        void RenderEnemy(float deltaTimeSecond);
        //void RenderBlockSquare(int translateX, int translateY);
        //Mesh* RenderWeapon(float R, float G, float B);
     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        int healt;
        int level;
        // Square
        float squareSide;
        int id;

        int randomObject;
        int randomPosition;
        float clock;
        bool addEnemy;
        bool generateStars;
        
        glm::vec3 corner;
        std::string squareCollorArray[6];
        std::string weaponCollorArray[5];
        std::string starCollorArray[5];
        std::string hexagonCollorArray[5];
        std::default_random_engine generator;
        std::vector<Enemy> enemyArray;
        // Time evidence
        std::chrono::seconds elapsedEnemyTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateEnemycurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateEnemyLastUpdateTime;
        std::chrono::seconds elapsedStarTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateStarcurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateStarLastUpdateTime;

        // TODO(student): If you need any other class variables, define them here.
    };
}   // namespace m1
