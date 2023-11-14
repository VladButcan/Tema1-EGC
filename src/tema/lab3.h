#pragma once

#include "components/simple_scene.h"
#include <random>
#include "Enemy.h"
#include "Weapon.h"
#include "Heart.h"
#include "Bullet.h"
#include "MoneyStars.h"
#include <chrono>



namespace tema
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:

        Lab3();
        ~Lab3();

        void Init() override;

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        // On Input Update Functions
        void OnInputUpdate(float deltaTime, int mods) override;
        //On Key press Functions
        void OnKeyPress(int key, int mods) override;
        void SkipLevel();
        //On Key Release Functions
        void OnKeyRelease(int key, int mods) override;
        // On Mouse Move Functions
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        // On Mouse Button Rress Functions
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void IndentifyMousePositionInWeaponBoxOnMouseButtonPress(int mouseX, int mouseY);
        void IndentifyMousePositionInBonusBoxOnMouseButtonPress(int mouseX, int mouseY);
        void IdentifyMousePositionInArenaBoxesOnMouseButtonPress(int mouseX, int mouseY, float &objectX, float &objectY);
        void SelectBonus(int mouseX, int mouseY);
        void DeleteWeapon(float objectPositionX, float objectPositionY);
        void SaveUpMoney(int mouseX, int mouseY);
        // On Mouse Button Release Functions
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void SpendMoney();
        // On Mouse Scrole Functions
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void ShowLevel();

        void GetTime();
        void InitLevelNumbers();
        void InitSquares();
        void InitWeapons();
        void InitStars();
        void InitHexagons();
        void RenderArenaSquares();
        void RenderHealt();
        void RenderAvaibleWeapons();
        void RenderBonuses();
        //void RenderPriceStars(int translateX, int translateY);
        void RenderAvaibleMoney();
        void RenderWeapon(float deltaTimeSecond);
        void RenderEnemy(float deltaTimeSecond);
        void AddEnemyInGame();
        void RenderBullet(float deltaTimeSecond);
        void GenerateBullet();
        void SetBulletDamageAndSpeed(Bullet &bullet);
        void EliminateEmeny();
        void CheckWeaponEnemyColision(std::vector<Enemy>::iterator enemy);
        bool CheckBulletEnemyColision(std::vector<Enemy>::iterator enemy);
        void RenderMoneyStars(float deltaTimeSecond);
        void EliminationByShrinking(float deltaTime);
        //void RenderBlockSquare(int translateX, int translateY);
        //Mesh* RenderWeapon(float R, float G, float B);

        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
     protected:
        //window
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix, matrixForRender;
        glm::ivec2 resolution;
        int mousePositionX, mousePositionY;


        float cx, cy;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        int playerHealt;
        // Square
        float squareSide;
        

        int randomObject;
        int randomPosition;
        float clock;
        bool addEnemy;
        float position;
        float angle;
        
        glm::vec3 corner;
        std::string squareCollorArray[6];
        std::string weaponCollorArray[5];
        std::string starCollorArray[5];
        std::string hexagonCollorArray[5];
        std::string numbersArray[10];
        std::random_device rd;

        // Buttons
        float S_On;
        float K_On;
        float I_On;
        float P_On;

        // Game
        int gameMoney;
        int id;
        float yResolution;
        float selectBonus;
        float newArenaSquares;
        int arenaSquares;


        //Money Stars
        float moneyStarsY;
        bool generateStarsBool;
        float rainbowIndex;

        // Bullet
        //damage
        float orangeBulletDamage;
        float blueBulletDamage;
        float yellowBulletDamage;
        float purpleBulletDamage;
        //speed
        float orangeBulletSpeed;
        float blueBulletSpeed;
        float yellowBulletSpeed;
        float purpleBulletSpeed;
        int firingSpeed;

        // Level
        int level;
        bool newLevel;
        std::string levelNumber;

        // Enemy
        int enemyPerLevel;
        int enemyCounter;
        int enemyFrequenceInMiliSec;
        float enemySpeed;

        // Weapon
        bool generateBulletBool;
        float weaponScale;
        std::string drawWeaponbyColor;

        // Arrays to stack data about objects
        std::vector<Enemy> enemyArray;
        std::vector<Weapon> weaponArray;
        std::vector<Bullet> bulletArray;
        std::vector<MoneyStars> moneyStarsArray;
        // Arrays to stack data about objects being in an eliminating process
        std::vector<Enemy> enemiesToEliminate;
        std::vector<Weapon> weaponsToEliminate;
        std::vector<MoneyStars> moneyStarsToEliminate;
        std::vector<Bullet> bulletToEliminate;
        std::vector<Bullet> indicesToEliminateBullets;
        std::vector<Enemy> indicesToEliminateEnemies;
        // Time evidence
        std::chrono::milliseconds elapsedEnemyTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateEnemycurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateEnemyLastUpdateTime;
        std::chrono::seconds elapsedStarTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateStarcurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateStarLastUpdateTime;
        std::chrono::seconds elapsedButtonTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateButtonCurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateButtonLastUpdateTime;

        // TODO(student): If you need any other class variables, define them here.
    };
}   // namespace m1
