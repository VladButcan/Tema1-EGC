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

        void ReinitVisualMatrix();
        void RenderBonusScene(float deltaTimeSeconds);
        void RenderGameScene(float deltaTimeSeconds);
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
        void IndentifyMousePositionInPauseBoxMouseButtonPress(int mouseX, int mouseY);
        void IdentifyMousePositionInArenaBoxesOnMouseButtonPress(int mouseX, int mouseY, float &objectX, float &objectY);
        void SelectBonusAndPassLevel(int mouseX, int mouseY);
        void DeleteWeapon(float objectPositionX, float objectPositionY);
        void SaveUpMoney(int mouseX, int mouseY);
        // On Mouse Button Release Functions
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void SpendMoney();
        // On Mouse Scrole Functions
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void ColorTheStar(float deltaTimeSecond);
        void ShowLevel();
        void GameSettings();
        void ValidateGameData(float &deltaTimeSeconds);

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
        void RenderCharacteristics();
        void RenderWeapon(float deltaTimeSecond);
        void RenderEnemy(float deltaTimeSecond);
        void AddEnemyInGame();
        void RenderBullet(float deltaTimeSecond);
        void GenerateBullet();
        void SetBulletDamageAndSpeed(Bullet &bullet);
        void EliminateEmeny();
        void CheckWeaponEnemyColision(std::vector<Enemy>::iterator enemy);
        bool CheckBulletEnemyColision(std::vector<Enemy>::iterator enemy);
        void DragAndDropMechanism();
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
        glm::vec3 corner;
        std::random_device rd;

        

        float cx, cy;
        float translateX, translateY;
        float scaleX, scaleY;
        float clock;

        // Square
        float squareSide;
        
        // Arrays for meshes
        std::string squareCollorArray[6];
        std::string weaponCollorArray[5];
        std::string starCollorArray[5];
        std::string hexagonCollorArray[5];
        std::string numbersArray[10];

        // Buttons
        bool S_On;
        bool K_On;
        bool I_On;
        bool P_On;

        // Game
        int playerHealt;
        int gameMoney;
        bool newArenaSquares;
        bool gamePause;
        int arenaSquares;
        int mousePositionX, mousePositionY;


        //Money Stars
        bool generateStarsBool;
        float rainbowIndex;

        // Bullet
        //damage
        int orangeBulletDamage;
        int blueBulletDamage;
        int yellowBulletDamage;
        int purpleBulletDamage;
        //speed
        int orangeBulletSpeed;
        int blueBulletSpeed;
        int yellowBulletSpeed;
        int purpleBulletSpeed;
        int firingSpeed;
        int firingFreq;

        // Level
        int level;
        bool newLevel;

        // Enemy
        int enemyPerLevel;
        int enemyCounter;
        int enemyFrequenceInMiliSec;
        int enemySpeed;
        int enemyHealt;
        bool addEnemy;

        // Weapon
        bool generateBulletBool;
        float weaponScale;
        std::string drawWeaponbyColor;

        // Arrays to stack data about objects
        std::vector<Heart> heartArray;
        std::vector<Enemy> enemyArray;
        std::vector<Weapon> weaponArray;
        std::vector<Bullet> bulletArray;
        std::vector<MoneyStars> moneyStarsArray;


        // Arrays to stack data about objects being in an eliminating process
        std::vector<Heart> heartsToEliminate;
        std::vector<Enemy> enemiesToEliminate;
        std::vector<Weapon> weaponsToEliminate;
        std::vector<MoneyStars> moneyStarsToEliminate;
        std::vector<Bullet> bulletToEliminate;

        // Time evidence

        std::chrono::milliseconds elapsedPauseTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> pauseCurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> pauseLastUpdateTime;
        std::chrono::milliseconds elapsedEnemyTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateEnemycurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateEnemyLastUpdateTime;
        std::chrono::milliseconds elapsedStarTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateStarcurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateStarLastUpdateTime;
        std::chrono::milliseconds elapsedButtonTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateButtonCurrentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> generateButtonLastUpdateTime;

    };
}
