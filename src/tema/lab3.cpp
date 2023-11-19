#include "tema/lab3.h"

#include <vector>
#include <iostream>

#include "tema/transform2D.h"
#include "tema/object2D.h"
#include "tema/Weapon.h"

using namespace std;
using namespace tema;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 1280;   // logic width
    logicSpace.height = 720;  // logic height

    // Declare matrix for render
    matrixForRender = glm::mat3(1);
    corner = glm::vec3(0, 0, 0);
    squareSide = 100;
    
    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 0;
    scaleY = 0;
    clock = 0.0;

    // Init level mnumbers meshes
    InitLevelNumbers();

    // Init figures
    //InitPlayerHealt();
    InitSquares();
    InitWeapons();
    InitStars();
    InitHexagons();

    //Game
    playerHealt = 4;
    gameMoney = 10;
    arenaSquares = 3;
    level = 1;
    newLevel = false;
    newArenaSquares = false;
    gamePause = false;
    elapsedPauseTime = std::chrono::milliseconds(0);

    // Enemy
    generateEnemyLastUpdateTime = std::chrono::high_resolution_clock::now();
    enemyPerLevel = level * 10;
    enemyHealt = 30;
    enemyCounter = 0;
    enemyFrequenceInMiliSec = 4000;
    enemySpeed = 50;
    addEnemy = false;

    // Weapon
    drawWeaponbyColor = "";
    weaponScale = 4.0f;

    // Bullet
    generateBulletBool = true;
    orangeBulletDamage = blueBulletDamage = yellowBulletDamage = purpleBulletDamage = 10;
    orangeBulletSpeed = blueBulletSpeed = yellowBulletSpeed = purpleBulletSpeed = 100;
    firingSpeed = 3000;
    firingFreq = 50;

    // Money Stars
    generateStarLastUpdateTime = generateEnemyLastUpdateTime;
    generateStarsBool = true;
    rainbowIndex = 0;
    
    // Mouse
    mousePositionX = mousePositionY = 0;

    // Scena
    AddMeshToList(object2D::CreateStar("rainbowStar", glm::vec3(1, 1, 1), true));
    AddMeshToList(object2D::CreateTextDMG("dmg", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateTextSPEED("speed", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateHeart("redHeart", glm::vec3(0.749, 0.067, 0.067), true));
    AddMeshToList(object2D::CreateCircle("whiteCircle", 0.0f, 0.0f, 4.0f, glm::vec3(1, 1, 1), true));
    AddMeshToList(object2D::CreateTriangle("whiteTriangle", glm::vec3(1, 1, 1), true));

    
}

void Lab3::InitLevelNumbers()
{
    numbersArray[0] = "zero";
    numbersArray[1] = "one";
    numbersArray[2] = "two";
    numbersArray[3] = "three";
    numbersArray[4] = "four";
    numbersArray[5] = "five";
    numbersArray[6] = "six";
    numbersArray[7] = "seven";
    numbersArray[8] = "eight";
    numbersArray[9] = "nine";
    AddMeshToList(object2D::CreateZero("zero", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateOne("one", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateTwo("two", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateThree("three", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateFour("four", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateFive("five", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateSix("six", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateSeven("seven", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateEight("eight", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateNine("nine", glm::vec3(1, 1, 1)));
}

void Lab3::InitSquares()
{
    // Define squares
    squareCollorArray[0] = "orangeSquare";
    squareCollorArray[1] = "blueSquare";
    squareCollorArray[2] = "yellowSquare";
    squareCollorArray[3] = "purpleSquare";
    squareCollorArray[4] = "redSquare";
    squareCollorArray[5] = "greenSquare";

    AddMeshToList(object2D::CreateSquare("redSquare", glm::vec3(0.749, 0.067, 0.067), true));

    AddMeshToList(object2D::CreateSquare("greenSquare", glm::vec3(0.208, 0.361, 0.071), true));

    AddMeshToList(object2D::CreateSquare("blueSquare", glm::vec3(0.439, 0.733, 0.839), true));

    AddMeshToList(object2D::CreateSquare("orangeSquare", glm::vec3(1, 0.5, 0), true));

    AddMeshToList(object2D::CreateSquare("yellowSquare", glm::vec3(0.929, 0.898, 0.643), true));

    AddMeshToList(object2D::CreateSquare("purpleSquare", glm::vec3(0.62, 0.408, 0.961), true));

    AddMeshToList(object2D::CreateSquare("whiteSquare", glm::vec3(1, 1, 1)));
    AddMeshToList(object2D::CreateSquare("whiteFillSquare", glm::vec3(1, 1, 1), true));
}

void Lab3::InitWeapons()
{
    // Define weapons
    weaponCollorArray[0] = "orangeWeapon";
    weaponCollorArray[1] = "blueWeapon";
    weaponCollorArray[2] = "yellowWeapon";
    weaponCollorArray[3] = "purpleWeapon";
    weaponCollorArray[4] = "redWeapon";

    AddMeshToList(object2D::CreateWeapon("redWeapon", glm::vec3(0.749, 0.067, 0.067), true));

    AddMeshToList(object2D::CreateWeapon("blueWeapon", glm::vec3(0.439, 0.733, 0.839), true));

    AddMeshToList(object2D::CreateWeapon("orangeWeapon", glm::vec3(0.961, 0.635, 0.086), true));

    AddMeshToList(object2D::CreateWeapon("yellowWeapon", glm::vec3(0.969, 0.914, 0.416), true));

    AddMeshToList(object2D::CreateWeapon("purpleWeapon", glm::vec3(0.62, 0.408, 0.961), true));

    AddMeshToList(object2D::CreateWeapon("whiteWeapon", glm::vec3(1, 1, 1), true));
}

void Lab3::InitStars()
{
    // Define stars
    starCollorArray[0] = "orangeStar";
    starCollorArray[1] = "blueStar";
    starCollorArray[2] = "yellowStar";
    starCollorArray[3] = "purpleStar";
    starCollorArray[4] = "redStar";

    AddMeshToList(object2D::CreateStar("redStar", glm::vec3(0.749, 0.067, 0.067), true));

    AddMeshToList(object2D::CreateStar("blueStar", glm::vec3(0.439, 0.733, 0.839), true));

    AddMeshToList(object2D::CreateStar("orangeStar", glm::vec3(0.961, 0.635, 0.086), true));

    AddMeshToList(object2D::CreateStar("yellowStar", glm::vec3(0.969, 0.914, 0.416), true));

    AddMeshToList(object2D::CreateStar("purpleStar", glm::vec3(0.62, 0.408, 0.961), true));

    AddMeshToList(object2D::CreateStar("whiteStar", glm::vec3(1, 1, 1), true));
}

void Lab3::InitHexagons()
{
    // Define stars
    hexagonCollorArray[0] = "orangeHexagon";
    hexagonCollorArray[1] = "blueHexagon";
    hexagonCollorArray[2] = "yellowHexagon";
    hexagonCollorArray[3] = "purpleHexagon";

    AddMeshToList(object2D::CreateHexagon("redHexagon", glm::vec3(0.749, 0.067, 0.067), true));

    AddMeshToList(object2D::CreateHexagon("blueHexagon", glm::vec3(0.439, 0.733, 0.839), true));
    // Blue inside color is green
    AddMeshToList(object2D::CreateHexagon("blueInsideColor", glm::vec3(0.886, 0.973, 1), true));

    AddMeshToList(object2D::CreateHexagon("orangeHexagon", glm::vec3(0.961, 0.635, 0.086), true));
    // Orange inside color is yellow
    AddMeshToList(object2D::CreateHexagon("orangeInsideColor", glm::vec3(0.988, 0.89, 0.561), true));

    AddMeshToList(object2D::CreateHexagon("yellowHexagon", glm::vec3(0.969, 0.914, 0.416), true));
    // Yellow inside color is green
    AddMeshToList(object2D::CreateHexagon("yellowInsideColor", glm::vec3(0.996, 1, 0.89), true));

    AddMeshToList(object2D::CreateHexagon("purpleHexagon", glm::vec3(0.62, 0.408, 0.961), true));
    // Purple inside color is cream
    AddMeshToList(object2D::CreateHexagon("purpleInsideColor", glm::vec3(1, 0.96, 0.76), true));

    AddMeshToList(object2D::CreateHexagon("whiteHexagon", glm::vec3(1, 1, 1), true));
}

// 2D visualization matrix
glm::mat3 Lab3::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Lab3::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Lab3::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}



void Lab3::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Lab3::Update(float deltaTimeSeconds)
{
    ReinitVisualMatrix();
    if (newLevel == true && enemyArray.size() == 0 && enemiesToEliminate.size() == 0) {
        RenderBonusScene(deltaTimeSeconds);
    }
    else {
        RenderGameScene(deltaTimeSeconds);
    }
}

void Lab3::ReinitVisualMatrix()
{
    resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
}

void Lab3::RenderGameScene(float deltaTimeSeconds)
{
    // Change color
    ColorTheStar(deltaTimeSeconds);
    ShowLevel();
    GameSettings();
    RenderArenaSquares();
    RenderHealt();
    RenderAvaibleWeapons();
    RenderBonuses();
    RenderAvaibleMoney();
    RenderCharacteristics();
    GetTime();
    ValidateGameData(deltaTimeSeconds);
    EliminationByShrinking(deltaTimeSeconds);
    RenderWeapon(deltaTimeSeconds);
    RenderEnemy(deltaTimeSeconds);
    RenderBullet(deltaTimeSeconds);
    DragAndDropMechanism();
    RenderMoneyStars(deltaTimeSeconds);
}

void Lab3::RenderBonusScene(float deltaTimeSeconds) {
    int DMG = level * 75 / 5;
    // Draw Left White Square
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x / 4, resolution.y / 2);
    modelMatrix *= transform2D::Scale(20, 20);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    modelMatrix *= transform2D::Translate(20, 10);
    // Draw DMG value
    while (DMG != 0) {
        RenderMesh2D(meshes[numbersArray[DMG % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-20, 0);
        DMG /= 10;
    }
    // Draw "+"
    modelMatrix *= transform2D::Scale(1, 0.3);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(0.3, 3);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    // Draw DMG Text
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x / 4, resolution.y / 2 - 60);
    modelMatrix *= transform2D::Scale(3, 3);
    RenderMesh2D(meshes["dmg"], shaders["VertexColor"], modelMatrix);
    // Draw Right White Square
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(3 * resolution.x / 4, resolution.y / 2);
    modelMatrix *= transform2D::Scale(20, 20);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    
    int SPEED = 50;
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    modelMatrix *= transform2D::Translate(20, 10);
    // Draw Speed Value
    while (SPEED != 0) {
        RenderMesh2D(meshes[numbersArray[SPEED % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-20, 0);
        SPEED /= 10;
    }
    // Draw "+"
    modelMatrix *= transform2D::Scale(1, 0.3);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(0.3, 3);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    // Draw SPEED Text
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(3 * resolution.x / 4, resolution.y / 2 - 60);
    modelMatrix *= transform2D::Scale(3, 3);
    RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

 /*
 ------------------------------------------------------------------------------------------
 On Input Update Functions
 ------------------------------------------------------------------------------------------
 */
void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    
}

/*
------------------------------------------------------------------------------------------
On Key Press Functions
------------------------------------------------------------------------------------------
*/
void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_S) {
        S_On = true;
    }
    if (key == GLFW_KEY_K) {
        if (S_On == true) K_On = true;
    }
    if (key == GLFW_KEY_I) {
        if (K_On == true) I_On = true;
    }
    if (key == GLFW_KEY_P) {
        if (I_On == true) SkipLevel();
    }
}

void Lab3::SkipLevel()
{
    newLevel = true;
    enemyArray.clear();
    bulletArray.clear();
    enemySpeed += std::round((enemyPerLevel - enemyCounter) / 5) * 5;
    enemyHealt += enemyPerLevel / 5 * 10;
}
/*
------------------------------------------------------------------------------------------
On Key Release Functions
------------------------------------------------------------------------------------------
*/
void Lab3::OnKeyRelease(int key, int mods)
{

}

/*
------------------------------------------------------------------------------------------
On Mouse Move Functions
------------------------------------------------------------------------------------------
*/
void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
        mousePositionX = mouseX;
        mousePositionY = mouseY;
}

/*
------------------------------------------------------------------------------------------
On Mouse Button Press Functions
------------------------------------------------------------------------------------------
*/
void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1) {
        if (newLevel == true && enemyArray.size() == 0 && enemiesToEliminate.size() == 0) {
            SelectBonusAndPassLevel(mouseX, mouseY);
        }
        IndentifyMousePositionInPauseBoxMouseButtonPress(mouseX, mouseY);
        if (gamePause == false) {
            SaveUpMoney(mouseX, mouseY);
            IndentifyMousePositionInWeaponBoxOnMouseButtonPress(mouseX, mouseY);
            IndentifyMousePositionInBonusBoxOnMouseButtonPress(mouseX, mouseY);
        }
        
    }

    if (button == 2) {
        if (gamePause == false) {
            float objectPositionX = 0.0f, objectPositionY = 0.0f;
            IdentifyMousePositionInArenaBoxesOnMouseButtonPress(mouseX, mouseY, objectPositionX, objectPositionY);
            if (objectPositionX != 0.0f && objectPositionY != 0.0f) DeleteWeapon(objectPositionX, objectPositionY);
        }
    }
}

void Lab3::IndentifyMousePositionInWeaponBoxOnMouseButtonPress(int mouseX, int mouseY) {
    if (mouseX >= 25 && mouseX <= 125 && mouseY <= 120 && mouseY >= 20) {
        if (gameMoney >= 1) drawWeaponbyColor = "orange";
    }
    else {
        if (mouseX >= 175 && mouseX <= 275 && mouseY <= 120 && mouseY >= 20) {
            if (gameMoney >= 2) drawWeaponbyColor = "blue";
        }
        else {
            if (mouseX >= 325 && mouseX <= 425 && mouseY <= 120 && mouseY >= 20) {
                if (gameMoney >= 3) drawWeaponbyColor = "yellow";
            }
            else {
                if (mouseX >= 475 && mouseX <= 575 && mouseY <= 120 && mouseY >= 20) {
                    if (gameMoney >= 4) drawWeaponbyColor = "purple";
                }
            }
        }
    }
}

void Lab3::IndentifyMousePositionInBonusBoxOnMouseButtonPress(int mouseX, int mouseY) {
    if (mouseX >= 25 && mouseX <= 125 && mouseY <= 250 && mouseY >= 150) {
        if (gameMoney >= 20) {
            orangeBulletDamage += 10;
            blueBulletDamage += 10;
            yellowBulletDamage += 10;
            purpleBulletDamage += 10;
            gameMoney -= 20;
        }
    }
    else {
        if (mouseX >= 175 && mouseX <= 275 && mouseY <= 250 && mouseY >= 150) {
            if (gameMoney >= 20) {
                firingSpeed -= 50;
                firingFreq += 50;
                gameMoney -= 20;
            }
        }
        else {
            if (mouseX >= 325 && mouseX <= 425 && mouseY <= 250 && mouseY >= 150) {
                if (gameMoney >= 20) {
                    orangeBulletSpeed += 10;
                    blueBulletSpeed += 10;
                    yellowBulletSpeed += 10;
                    purpleBulletSpeed += 10;
                    gameMoney -= 20;
                }
            }
            else {
                if (mouseX >= 475 && mouseX <= 575 && mouseY <= 250 && mouseY >= 150) {
                    if (newArenaSquares == false) {
                        if (gameMoney >= 300) {
                            newArenaSquares = true;
                            arenaSquares++;
                            gameMoney -= 300;
                        }
                    }
                }
            }
        }
    }
}

void Lab3::IdentifyMousePositionInArenaBoxesOnMouseButtonPress(int mouseX, int mouseY, float &objectPositionX, float &objectPositionY) {
    if (mouseX >= 75 && mouseX <= 175) {
        objectPositionX = 75;
    }
    else {
        if (mouseX >= 225 && mouseX <= 325) {
            objectPositionX = 225;
        }
        else {
            if (mouseX >= 375 && mouseX <= 475) {
                objectPositionX = 375;
            }
            else {
                if (newArenaSquares == true) {
                    if (mouseX >= 525 && mouseX <= 625) {
                        objectPositionX = 525;
                    }
                }
            }
        }
    }

    if (mouseY <= resolution.y - 25 && mouseY >= resolution.y - 125) {
        objectPositionY = 25;
    }
    else {
        if (mouseY <= resolution.y - 165 && mouseY >= resolution.y - 265) {
            objectPositionY = 165;
        }
        else {
            if (mouseY <= resolution.y - 305 && mouseY >= resolution.y - 405) {
                objectPositionY = 305;
            }
            else {
                if (newArenaSquares == true) {
                    if (mouseY <= resolution.y - 445 && mouseY >= resolution.y - 545) {
                        objectPositionY = 445;
                    }
                }
            }
        }
    }
}

void Lab3::IndentifyMousePositionInPauseBoxMouseButtonPress(int mouseX, int mouseY) {
    if (mouseX >= resolution.x / 2 - 30 && mouseX <= resolution.x / 2 + 30 && mouseY <= 80 && mouseY >= 20) {
        if (gamePause == true) gamePause = false;
        else gamePause = true;
    }
}

void Lab3::SelectBonusAndPassLevel(int mouseX, int mouseY)
{
    if (mouseX >= resolution.x / 4 - 200
        && mouseX <= resolution.x / 4 + 200
        && mouseY >= resolution.y / 2 - 200
        && mouseY <= resolution.y / 2 + 200
        ) {
        orangeBulletDamage += level * 75 / 5;
        blueBulletDamage += level * 75 / 5;
        yellowBulletDamage += level * 75 / 5;
        purpleBulletDamage += level * 75 / 5;
        newLevel = false;
        level += 1;
        if (level % 2 == 0 && enemyFrequenceInMiliSec > 500) {
            enemyFrequenceInMiliSec -= 500;
        }
        enemyPerLevel += 10;
        enemyCounter = 0;
        bulletArray.clear();
    }
    else {
        if (mouseX >= 3 * resolution.x / 4 - 200
            && mouseX <= 3 * resolution.x / 4 + 200
            && mouseY >= resolution.y / 2 - 200
            && mouseY <= resolution.y / 2 + 200
            ) {
            orangeBulletSpeed += 25;
            blueBulletSpeed += 25;
            yellowBulletSpeed += 25;
            purpleBulletSpeed += 25;
            newLevel = false;
            level += 1;
            if (level % 2 == 0 && enemyFrequenceInMiliSec > 500) {
                enemyFrequenceInMiliSec -= 500;
            }
            enemyPerLevel += 10;
            enemyCounter = 0;
            bulletArray.clear();
        }
    }
}

void Lab3::DeleteWeapon(float objectPositionX, float objectPositionY)
{
    objectPositionX += 50.0f;
    objectPositionY += 50.0f;
    bool freePosition = true;
    int i = 0;
    for (i = 0; i < weaponArray.size(); i++) {
        if (weaponArray[i].getPosX() == objectPositionX && weaponArray[i].getPosY() == objectPositionY) {
            freePosition = false;
            break;
        }
    }
    if (freePosition == false) {
        weaponsToEliminate.push_back(weaponArray[i]);
        weaponArray.erase(weaponArray.begin() + i);
    }
}

void Lab3::SaveUpMoney(int mouseX, int mouseY)
{
    for (auto money = moneyStarsArray.begin(); money != moneyStarsArray.end();) {
        if (mouseX >= money->getPosX() - 20
            && mouseX <= money->getPosX() + 20
            && mouseY <= resolution.y - (money->getPosY() - 20)
            && mouseY >= resolution.y - (money->getPosY() + 20)) {
            moneyStarsToEliminate.push_back(*money);
            money = moneyStarsArray.erase(money);
            gameMoney++;
        }
        else {
            ++money;
        }
    }
}

/*
------------------------------------------------------------------------------------------
On Mouse Button Release Functions
------------------------------------------------------------------------------------------
*/
void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 1) {
        float generateObjectX = 0.0f, generateObjectY = 0.0f;
        if (mouseX >= 75 && mouseX <= 175) {
            generateObjectX = 75 + (0 * 2 * 75);
        }
        else {
            if (mouseX >= 225 && mouseX <= 325) {
                generateObjectX = 75 + (1 * 2 * 75);
            }
            else {
                if (mouseX >= 375 && mouseX <= 475) {
                    generateObjectX = 75 + (2 * 2 * 75);
                }
                else {
                    if (newArenaSquares == true) {
                        if (mouseX >= 525 && mouseX <= 625) {
                            generateObjectX = 525;
                        }
                    }
                }
            }
        }

        if (mouseY <= resolution.y - 25 && mouseY >= resolution.y - 125) {
            generateObjectY = (25 + (0 % 3 * 140));
        }
        else {
            if (mouseY <= resolution.y - 165 && mouseY >= resolution.y - 265) {
                generateObjectY = (25 + (1 % 3 * 140));
            }
            else {
                if (mouseY <= resolution.y - 305 && mouseY >= resolution.y - 405) {
                    generateObjectY = (25 + (2 % 3 * 140));
                }
                else {
                    if (newArenaSquares == true) {
                        if (mouseY <= resolution.y - 445 && mouseY >= resolution.y - 545) {
                            generateObjectY = 445;
                        }
                    }
                }
            }
        }
        if (generateObjectX != 0.0f && generateObjectY != 0.0f) {
            generateObjectX += 50.0f;
            generateObjectY += 50.0f;
            bool freePosition = true;
            for (int i = 0; i < weaponArray.size(); i++) {
                if (weaponArray[i].getPosX() == generateObjectX && weaponArray[i].getPosY() == generateObjectY) {
                    freePosition = false;
                    break;
                }
            }
            if (freePosition == true && drawWeaponbyColor != "") {
                Weapon weapon(drawWeaponbyColor, generateObjectX, generateObjectY, weaponScale, 5 * weaponScale);
                weapon.lastUpdateTime = std::chrono::high_resolution_clock::now();
                weapon.renderBullet = true;
                weaponArray.push_back(weapon);
                SpendMoney();
            }
        }
        drawWeaponbyColor = "";
    }
}

void Lab3::SpendMoney() {
    if (drawWeaponbyColor == "orange") {
        gameMoney -= 1;
    }
    else {
        if (drawWeaponbyColor == "blue") {
            gameMoney -= 2;
        }
        else {
            if (drawWeaponbyColor == "yellow") {
                gameMoney -= 3;
            }
            else {
                if (drawWeaponbyColor == "purple") {
                    gameMoney -= 4;
                }
            }
        }
    }
}


/*
------------------------------------------------------------------------------------------
On Mouse Scroll Functions
------------------------------------------------------------------------------------------
*/
void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}

void Lab3::ColorTheStar(float deltaTimeSeconds) {
    rainbowIndex += deltaTimeSeconds;
    float red = 0.5f + 0.5f * sin(rainbowIndex);
    float green = 0.5f + 0.5f * sin(rainbowIndex + 2.0f);
    float blue = 0.5f + 0.5f * sin(rainbowIndex + 4.0f);
    AddMeshToList(object2D::CreateStar("rainbowStar", glm::vec3(red, green, blue), true));
}

void Lab3::ShowLevel()
{
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x / 2, 3 * resolution.y / 4);
    modelMatrix *= transform2D::Scale(10, 10);
    int copy = level;
    while (copy != 0) {
        RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-20, 0);
        copy /= 10;
    }
}

void Lab3::GameSettings()
{
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x / 2, resolution.y - 50);
    modelMatrix *= transform2D::Scale(3, 3);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(0.5, 0.5);
    if (gamePause == false) {
        modelMatrix *= transform2D::Rotate(-3.14 / 2);
        RenderMesh2D(meshes["whiteTriangle"], shaders["VertexColor"], modelMatrix);
    }
    else {
        modelMatrix *= transform2D::Translate(-8, 0);
        modelMatrix *= transform2D::Scale(0.4, 1);
        RenderMesh2D(meshes["whiteFillSquare"], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(40, 0);
        RenderMesh2D(meshes["whiteFillSquare"], shaders["VertexColor"], modelMatrix);
    }
    
}

void Lab3::GetTime() {
    // Get time moment
    currentTime = std::chrono::high_resolution_clock::now();
    if (gamePause == true) {
        generateEnemyLastUpdateTime = currentTime;
        generateButtonLastUpdateTime = currentTime;
        generateStarLastUpdateTime = currentTime;
    }
    // Enemy generator
    generateEnemycurrentTime = currentTime;
    elapsedEnemyTime = std::chrono::duration_cast<std::chrono::milliseconds>(generateEnemycurrentTime - generateEnemyLastUpdateTime);
    if (elapsedEnemyTime >= std::chrono::milliseconds(enemyFrequenceInMiliSec) && gamePause == false) {
        generateEnemyLastUpdateTime = generateEnemycurrentTime;
        addEnemy = true;
        enemyCounter++;

        if (enemyCounter == enemyPerLevel) {
            newLevel = true;
        }

    }

    // Button reset
    generateButtonCurrentTime = currentTime;
    elapsedButtonTime = std::chrono::duration_cast<std::chrono::milliseconds>(generateButtonCurrentTime - generateButtonLastUpdateTime);
    if (elapsedButtonTime >= std::chrono::milliseconds(4000) && gamePause == false) {
        generateButtonLastUpdateTime = generateButtonCurrentTime;
        S_On = false;
        K_On = false;
        I_On = false;
        P_On = false;
    }

    // Money generator
    generateStarcurrentTime = currentTime;
    elapsedStarTime = std::chrono::duration_cast<std::chrono::milliseconds>(generateStarcurrentTime - generateStarLastUpdateTime);
    if (elapsedStarTime >= std::chrono::milliseconds(3000) && gamePause == false) {
        generateStarLastUpdateTime = generateStarcurrentTime;
        generateStarsBool = true;
    }

    // Weapon shooting timer
    for (auto weapon = weaponArray.begin(); weapon != weaponArray.end();) {
        weapon->currentTime = std::chrono::high_resolution_clock::now();
        weapon->elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(weapon->currentTime - weapon->lastUpdateTime);
        if (weapon->elapsedTime >= std::chrono::milliseconds(firingSpeed)) {
            weapon->lastUpdateTime = weapon->currentTime;
            if (gamePause == false) weapon->renderBullet = true;
        }
        ++weapon;
    }
}
void Lab3::ValidateGameData(float &deltaTimeSeconds)
{
    if (gamePause == true) {
        deltaTimeSeconds = 0;
    }
    if (playerHealt <= 0) {
        enemyArray.clear();
        weaponArray.clear();
        moneyStarsArray.clear();
        bulletArray.clear();
        Init();
    }
}



void Lab3::RenderArenaSquares()
{

    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(30, 215);
    modelMatrix *= transform2D::Scale(2, 20);
    RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < arenaSquares; j++) {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
            modelMatrix *= transform2D::Translate(75 + (j * 2 * 75), 25 + (i % 3 * 140));
            modelMatrix *= transform2D::Scale(6, 6);
            RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);
        }
    }
}


void Lab3::RenderHealt()
{
    for (int i = 0; i < playerHealt; i++) {
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(resolution.x - 60 - (i * 2 * 60), resolution.y - 50);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["redHeart"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::RenderAvaibleWeapons()
{
    int translateX, translateY;
    for (int i = 0; i < 4; i++) {
        translateX = 25 + (i * 2 * 75);
        translateY = resolution.y - 100;
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Scale(weaponScale, weaponScale);
        RenderMesh2D(meshes[weaponCollorArray[i]], shaders["VertexColor"], modelMatrix);
        
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(translateX + 35, translateY - 25);
        //modelMatrix *= transform2D::Scale(1, 1);
        RenderMesh2D(meshes[numbersArray[i + 1]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(30, 0);
        modelMatrix *= transform2D::Scale(1.5, 1.5);
        RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::RenderAvaibleMoney()
{
    int copy = gameMoney;
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x - 60, resolution.y - 145);
    while (copy != 0) {
        RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-25, 0);
        copy /= 10;
    }

    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x - 30, resolution.y - 145);
    modelMatrix *= transform2D::Scale(1.5, 1.5);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
}

void Lab3::RenderCharacteristics()
{
    int copy = blueBulletDamage;
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x - 60, resolution.y - 180);
    while (copy != 0) {
        RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-25, 0);
        copy /= 10;
    }
    modelMatrix *= transform2D::Translate(-25, 0);
    RenderMesh2D(meshes["dmg"], shaders["VertexColor"], modelMatrix);

    //----------------------------------------------------------------------------------------
    copy = blueBulletSpeed;
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x - 60, resolution.y - 220);
    while (copy != 0) {
        RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-25, 0);
        copy /= 10;
    }
    modelMatrix *= transform2D::Translate(-25, 0);
    RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(-50, 0);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);

    //----------------------------------------------------------------------------------------
    copy = firingFreq;
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x - 60, resolution.y - 260);
    while (copy != 0) {
        RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-25, 0);
        copy /= 10;
    }
    modelMatrix *= transform2D::Translate(-25, 0);
    RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(-50, 0);
    RenderMesh2D(meshes["whiteWeapon"], shaders["VertexColor"], modelMatrix);

    //----------------------------------------------------------------------------------------
    copy = enemySpeed;
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(resolution.x - 60, resolution.y - 300);
    while (copy != 0) {
        RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Translate(-25, 0);
        copy /= 10;
    }
    modelMatrix *= transform2D::Translate(-25, 0);
    RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(-50, 0);
    RenderMesh2D(meshes["whiteHexagon"], shaders["VertexColor"], modelMatrix);
}


void Lab3::RenderWeapon(float deltaTime)
{
    for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
        CheckWeaponEnemyColision(enemy);
        ++enemy;
    }
    for (int i = 0; i < weaponArray.size(); i++) {
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(weaponArray[i].getPosX(), weaponArray[i].getPosY());
        modelMatrix *= transform2D::Scale(weaponArray[i].getSize(), weaponArray[i].getSize());
        RenderMesh2D(meshes[weaponArray[i].getColor() + "Weapon"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::CheckWeaponEnemyColision(std::vector<Enemy>::iterator enemy)
{
    for (auto weapon = weaponArray.begin(); weapon != weaponArray.end();) {
        if (enemy->getPosY() == weapon->getPosY()) {
            if (enemy->getPosX() > weapon->getPosX() && (enemy->getPosX() - weapon->getPosX() <= enemy->getRadius() + weapon->getRadius())) {
                weaponsToEliminate.push_back(*weapon);
                weapon = weaponArray.erase(weapon);
            }
            else {
                ++weapon;
            }
        }
        else {
            ++weapon;
        }
    }
}



void Lab3::RenderEnemy(float deltaTime)
{
    
    if (addEnemy == true 
        && newLevel == false 
        && gamePause == false 
        && playerHealt > 0
        ) {
        addEnemy = false;
        if (enemyCounter % 5 == 0) {
            enemySpeed += 5;
            enemyHealt += 5;
        }
        AddEnemyInGame();
    }

    for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
        if (enemy->getPosX() <= 75.0f) {
            Heart heart("redHeart", resolution.x - 60 - ((playerHealt - 1) * 2 * 60), resolution.y - 50, 5.0f);
            heartsToEliminate.push_back(heart);
            playerHealt -= 1;
            enemiesToEliminate.push_back(*enemy);
            enemy = enemyArray.erase(enemy);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(enemy->getPosX() - enemySpeed * deltaTime, enemy->getPosY());
            modelMatrix *= transform2D::Scale(enemy->getSize(), enemy->getSize());

            enemy->setPosX(enemy->getPosX() - enemySpeed * deltaTime);
            RenderMesh2D(meshes[enemy->getColor() + "Hexagon"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Scale(0.7, 0.7);
            RenderMesh2D(meshes[enemy->getColor() + "InsideColor"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(2.5, -20);
            modelMatrix *= transform2D::Scale(0.4, 0.4);
            int copy = enemy->getHealt();
            while (copy != 0) {
                RenderMesh2D(meshes[numbersArray[copy % 10]], shaders["VertexColor"], modelMatrix);
                modelMatrix *= transform2D::Translate(-20, 0);
                copy /= 10;
            }
            ++enemy;
        }
    }
}


void Lab3::AddEnemyInGame() {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution1(0, 1000);
    int randomObject = distribution1(generator) % 4;
    std::uniform_int_distribution<int> distribution2(0, 1000);
    int randomPosition = distribution2(generator) % 3;

    std::string color = hexagonCollorArray[randomObject];
    size_t pos = color.find("Hexagon");
    color.erase(pos, 7);
    Enemy enemy(color, resolution.x, 75.0f + (randomPosition % 3 * 140), 3.0f);
    enemy.setRadius(enemy.getRadius() * 3.0f);
    enemy.setSpeed(enemySpeed);
    enemy.setHealt(enemy.getHealt() + enemyHealt);
    enemyArray.push_back(enemy);
}


void Lab3::RenderBullet(float deltaTimeSecond)
{
    GenerateBullet();
    EliminateEmeny();

    for (auto bullet = bulletArray.begin(); bullet != bulletArray.end();) {

        if (bullet->getPosX() > resolution.x) {
            bulletToEliminate.push_back(*bullet);
            bullet = bulletArray.erase(bullet);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(bullet->getPosX(), bullet->getPosY());
            modelMatrix *= transform2D::Scale(bullet->getSize(), bullet->getSize());
            modelMatrix *= transform2D::Rotate(-bullet->getAngle());
            RenderMesh2D(meshes[bullet->getColor() + "Star"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Rotate(-0.65);
            RenderMesh2D(meshes[bullet->getColor() + "Star"], shaders["VertexColor"], modelMatrix);
            bullet->setPosX(bullet->getPosX() + bullet->speed * deltaTimeSecond);
            bullet->setAngle(bullet->getAngle() + 3 * deltaTimeSecond);
            ++bullet;
        }
    }
}


void Lab3::GenerateBullet() {
    bool genBullet = false;
    for (auto weapon = weaponArray.begin(); weapon != weaponArray.end();) {
        genBullet = false;
        if (weapon->renderBullet == true) {
            weapon->renderBullet = false;
            for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
                if (weapon->getPosY() == enemy->getPosY() && weapon->getColor() == enemy->getColor()) {
                    genBullet = true;
                }
                ++enemy;
            }
        }
        if (genBullet == true && gamePause == false) {
            Bullet bullet(weapon->getColor(), weapon->getPosX() + 20.0f, weapon->getPosY(), 2.0f, 2.0f);
            bullet.setRadius(bullet.getRadius() * 3.0f);
            SetBulletDamageAndSpeed(bullet);
            bulletArray.push_back(bullet);
        }
        ++weapon;
    }
}

void Lab3::SetBulletDamageAndSpeed(Bullet &bullet)
{
    if (bullet.getColor() == "blue") {
        bullet.damage = blueBulletDamage;
        bullet.speed = blueBulletSpeed;
    }
    else {
        if (bullet.getColor() == "orange") {
            bullet.damage = orangeBulletDamage;
            bullet.speed = orangeBulletSpeed;
        }
        else {
            if (bullet.getColor() == "yellow") {
                bullet.damage = yellowBulletDamage;
                bullet.speed = yellowBulletSpeed;
            }
            else {
                if (bullet.getColor() == "purple") {
                    bullet.damage = purpleBulletDamage;
                    bullet.speed = purpleBulletSpeed;
                }
            }
        }
    }
}

void Lab3::EliminateEmeny()
{
    bool enemyElimination = false;
    for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
        enemyElimination = false;
        enemyElimination = CheckBulletEnemyColision(enemy);
        if (enemyElimination == true) {
            if (enemy->getHealt() <= 0) {
                if (enemy->getColor() == "orange" || enemy->getColor() == "blue") gameMoney += 4;
                if (enemy->getColor() == "yellow" || enemy->getColor() == "purple") gameMoney += 6;
                enemiesToEliminate.push_back(*enemy);
                enemy = enemyArray.erase(enemy);
            }
            else {
                ++enemy;
            }

        }
        else {
            ++enemy;
        }
    }
}

bool Lab3::CheckBulletEnemyColision(std::vector<Enemy>::iterator enemy)
{
    bool enemyElimination = false;
    for (auto bullet = bulletArray.begin(); bullet != bulletArray.end();) {
        if (bullet->getPosY() == enemy->getPosY() && bullet->getColor() == enemy->getColor()) {
            if ((enemy->getPosX() > bullet->getPosX()) && (enemy->getPosX() - bullet->getPosX() <= enemy->getRadius() + bullet->getRadius())) {
                enemyElimination = true;
                enemy->setHealt(enemy->getHealt() - bullet->damage);
                bulletToEliminate.push_back(*bullet);
                bullet = bulletArray.erase(bullet);
            }
            else {
                ++bullet;
            }
        }
        else {
            ++bullet;
        }
    }
    return enemyElimination;
}

void Lab3::DragAndDropMechanism() {
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(mousePositionX, resolution.y - mousePositionY);
    modelMatrix *= transform2D::Scale(weaponScale, weaponScale);
    RenderMesh2D(meshes[drawWeaponbyColor + "Weapon"], shaders["VertexColor"], modelMatrix);
}

void Lab3::RenderMoneyStars(float deltaTimeSecond)
{
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution1(600, resolution.x);

    if (generateStarsBool == true 
        && gamePause == false 
        && playerHealt > 0
        ) {
        generateStarsBool = false;
        int xPos = distribution1(generator);
        MoneyStars moneyStar("rainbowStar", xPos, resolution.y - 100, 3.0f);
        moneyStarsArray.push_back(moneyStar);
    }

    for (auto money = moneyStarsArray.begin(); money != moneyStarsArray.end();) {
        if (money->getPosY() <= 5) {
            //moneyStarsToEliminate.push_back(money);
            moneyStarsToEliminate.push_back(*money);
            money = moneyStarsArray.erase(money);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(money->getPosX(), money->getPosY());
            modelMatrix *= transform2D::Scale(money->getSize(), money->getSize());
            RenderMesh2D(meshes["rainbowStar"], shaders["VertexColor"], modelMatrix);
            money->setPosY(money->getPosY() - 30 * deltaTimeSecond);
            ++money;
        }
    }
}


void Lab3::EliminationByShrinking(float deltaTime)
{
    for (auto enemy = enemiesToEliminate.begin(); enemy != enemiesToEliminate.end();) {
        float size = enemy->getSize();
        size -= 5 * deltaTime;
        if (size <= 0.02) {
            enemy = enemiesToEliminate.erase(enemy);
        }
        else {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemy->getPosX(), enemy->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            enemy->setSize(size);
            RenderMesh2D(meshes[enemy->getColor() + "Hexagon"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Scale(0.6, 0.6);
            RenderMesh2D(meshes[enemy->getColor() + "InsideColor"], shaders["VertexColor"], modelMatrix);
            ++enemy;
        }
    }

    for (auto weapon = weaponsToEliminate.begin(); weapon != weaponsToEliminate.end();) {
        float size = weapon->getSize();
        size -= 5 * deltaTime;
        if (size <= 0.02) {
            weapon = weaponsToEliminate.erase(weapon);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(weapon->getPosX(), weapon->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            weapon->setSize(size);
            RenderMesh2D(meshes[weapon->getColor() + "Weapon"], shaders["VertexColor"], modelMatrix);
            ++weapon;
        }
    }

    for (auto money = moneyStarsToEliminate.begin(); money != moneyStarsToEliminate.end();) {
        float size = money->getSize();
        size -= 5 * deltaTime;
        if (size <= 0.02) {
            money = moneyStarsToEliminate.erase(money);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(money->getPosX(), money->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            money->setSize(size);
            RenderMesh2D(meshes[money->getColor()], shaders["VertexColor"], modelMatrix);
            ++money;
        }
    }

    for (auto bullet = bulletToEliminate.begin(); bullet != bulletToEliminate.end();) {
        float size = bullet->getSize();
        size -= 5 * deltaTime;
        if (size <= 0.02) {
            bullet = bulletToEliminate.erase(bullet);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(bullet->getPosX(), bullet->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            modelMatrix *= transform2D::Rotate(-bullet->getAngle());
            RenderMesh2D(meshes[bullet->getColor() + "Star"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Rotate(-0.65);
            RenderMesh2D(meshes[bullet->getColor() + "Star"], shaders["VertexColor"], modelMatrix);
            bullet->setSize(size);
            ++bullet;
        }
    }

    for (auto heart = heartsToEliminate.begin(); heart != heartsToEliminate.end();) {
        float size = heart->getSize();
        size -= 5 * deltaTime;
        if (size <= 0.02) {
            heart = heartsToEliminate.erase(heart);
        }
        else {
            modelMatrix = matrixForRender;
            modelMatrix *= transform2D::Translate(heart->getPosX(), heart->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            heart->setSize(size);
            RenderMesh2D(meshes[heart->getColor()], shaders["VertexColor"], modelMatrix);
            ++heart;
        }
    }
}


void Lab3::RenderBonuses()
{
    // Render DMG Bonus
    // ===================================================================================
    float translateX = 25 + (0 * 2 * 75);
    float translateY = resolution.y - 300;
    //if (resolution.y < 900) {
        translateY += 50;
    //}
    // Render White Box
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Scale(5, 5);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    // Render Bonus ----------------------------------------------------------------------
    // Render Plus
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY + 10);
    modelMatrix *= transform2D::Translate(-25, 0);
    modelMatrix *= transform2D::Scale(0.2, 1);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(5, 0.2);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    // Render 1
    modelMatrix *= transform2D::Translate(20, 0);
    modelMatrix *= transform2D::Scale(1, 5);
    RenderMesh2D(meshes[numbersArray[1]], shaders["VertexColor"], modelMatrix);
    //Render 0
    modelMatrix *= transform2D::Translate(20, 0);
    RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
    //Render DMG text
    modelMatrix *= transform2D::Translate(-15, -40);
    modelMatrix *= transform2D::Scale(0.8, 0.8);
    RenderMesh2D(meshes["dmg"], shaders["VertexColor"], modelMatrix);
    // ---------------------------------------------------------------------- Render Bonus

    // Render Price ----------------------------------------------------------------------
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(translateX + 25, translateY - 25);
    RenderMesh2D(meshes[numbersArray[2]], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(30, 0);
    RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
    // Render star
    modelMatrix *= transform2D::Translate(30, 0);
    modelMatrix *= transform2D::Scale(1.5, 1.5);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
    // ---------------------------------------------------------------------- Render Price
    // ===================================================================================



    // Render Weapon Speed Bonus
    // ===================================================================================
    translateX = 25 + (1 * 2 * 75);
    // Render White Box
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Scale(5, 5);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    // Render Bonus ---------------------------------------------------------------------
    // Render Plus
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY + 10);
    modelMatrix *= transform2D::Translate(-25, 0);
    modelMatrix *= transform2D::Scale(0.2, 1);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(5, 0.2);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    // Render 5
    modelMatrix *= transform2D::Translate(25, 0);
    modelMatrix *= transform2D::Scale(1, 5);
    RenderMesh2D(meshes[numbersArray[5]], shaders["VertexColor"], modelMatrix);
    //Render 0
    modelMatrix *= transform2D::Translate(20, 0);
    RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
    //Render SPEED text
    modelMatrix *= transform2D::Translate(-55, -40);
    modelMatrix *= transform2D::Scale(1.2, 1.2);
    RenderMesh2D(meshes["whiteWeapon"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    modelMatrix *= transform2D::Scale(0.7, 0.7);
    RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);
    // ---------------------------------------------------------------------- Render Bonus

    // Render Price ----------------------------------------------------------------------
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(translateX + 25, translateY - 25);
    RenderMesh2D(meshes[numbersArray[2]], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(30, 0);
    RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
    // Render star
    modelMatrix *= transform2D::Translate(30, 0);
    modelMatrix *= transform2D::Scale(1.5, 1.5);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
    // ---------------------------------------------------------------------- Render Price
    // ===================================================================================



    // Render Bullet Speed Bonus
    // ===================================================================================
    translateX = 25 + (2 * 2 * 75);
    // Render White Box
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Scale(5, 5);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

    // Render Bonus ----------------------------------------------------------------------
    // Render Plus
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
    modelMatrix *= transform2D::Translate(translateX, translateY + 10);
    modelMatrix *= transform2D::Translate(-20, 0);
    modelMatrix *= transform2D::Scale(0.2, 1);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(5, 0.2);
    RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);
    // Render 1
    modelMatrix *= transform2D::Translate(20, 0);
    modelMatrix *= transform2D::Scale(1, 5);
    RenderMesh2D(meshes[numbersArray[1]], shaders["VertexColor"], modelMatrix);
    //Render 0
    modelMatrix *= transform2D::Translate(20, 0);
    RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
    //Render SPEED text
    modelMatrix *= transform2D::Translate(-50, -40);
    //modelMatrix *= transform2D::Scale(0.8, 0.8);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    modelMatrix *= transform2D::Scale(0.8, 0.8);
    RenderMesh2D(meshes["speed"], shaders["VertexColor"], modelMatrix);
    // ---------------------------------------------------------------------- Render Bonus

    // Render Price ----------------------------------------------------------------------
    modelMatrix = matrixForRender;
    modelMatrix *= transform2D::Translate(translateX + 25, translateY - 25);
    RenderMesh2D(meshes[numbersArray[2]], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(30, 0);
    RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
    // Render star
    modelMatrix *= transform2D::Translate(30, 0);
    modelMatrix *= transform2D::Scale(1.5, 1.5);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
    // ---------------------------------------------------------------------- Render Price
    // ===================================================================================


    // Render New Arena Squares Bonus
    // ===================================================================================
    if (newArenaSquares == false) {
        translateX = 25 + (3 * 2 * 75);
        // Render White Box
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["whiteSquare"], shaders["VertexColor"], modelMatrix);

        // Render Bonus ------------------------------------------------------------------
        // Render Green Square
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);
        // Render Green Square
        modelMatrix *= transform2D::Translate(0, 100 / 3);
        RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);
        // Render Green Square
        modelMatrix *= transform2D::Translate(0, -200 / 3);
        RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);
        //  ----------------------------------------------------------------- Render Bonus

        // Render Price ------------------------------------------------------------------
        // Render 3
        modelMatrix = matrixForRender;
        modelMatrix *= transform2D::Translate(translateX, translateY - 25);
        RenderMesh2D(meshes[numbersArray[3]], shaders["VertexColor"], modelMatrix);
        // Render 0
        modelMatrix *= transform2D::Translate(30, 0);
        RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
        // Render 0
        modelMatrix *= transform2D::Translate(30, 0);
        RenderMesh2D(meshes[numbersArray[0]], shaders["VertexColor"], modelMatrix);
        // Render Star
        modelMatrix *= transform2D::Translate(30, 0);
        modelMatrix *= transform2D::Scale(1.5, 1.5);
        RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
        // ------------------------------------------------------------------ Render Price
    }
    // ===================================================================================
}
