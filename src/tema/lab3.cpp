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

    corner = glm::vec3(0, 0, 0);
    squareSide = 100;
    
    // Initialize tx and ty (the translation steps)
    translateX = 50;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;
    clock = 0.0;

    angle = 0.0;


    position = 75;

    id = 0;
    
    angularStep = 0;
    // Init figures
    InitSquares();
    InitWeapons();
    InitStars();
    InitHexagons();
    AddMeshToList(object2D::CreateHeart("heart", glm::vec3(1, 0, 0), true));


    generateEnemyLastUpdateTime = std::chrono::high_resolution_clock::now();
    generateStarLastUpdateTime = generateEnemyLastUpdateTime;

    //Game
    playerHealt = 4;
    gameMoney = 4;
    addEnemy = false;
    generateStarsBool = true;
    generateBulletBool = true;
    drawWeaponbyColor = "";
    weaponScale = 4.0f;
    dropTimer = 10.0f;
    moneyStarsY = 700.0f;

    mousePositionX = mousePositionY = 0;

    //Scena


    
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
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glm::ivec2 resolution = window->GetResolution();
    //// Sets the screen area where to draw
    //glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    //cout << "x = " << resolution.x << endl << "y = " << resolution.y << endl;
    SetViewportArea(viewSpace, glm::vec3(0), true);
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

    RenderArenaSquares();
    RenderHealt();
    RenderAvaibleWeapons();
    RenderAvaibleMoney();
    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 25);
    RenderMesh2D(meshes["hexagon"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(650, 75);
    modelMatrix *= transform2D::Scale(0.8, 0.8);
    modelMatrix *= transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["hexagon"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(900, 25);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);*/

    GetTime(deltaTimeSeconds);

    if (playerHealt <= 0) {
        addEnemy = false;
    }
    
    RenderWeapon(deltaTimeSeconds);
    RenderEnemy(deltaTimeSeconds);
    RenderBullet(deltaTimeSeconds, 0.0f);
    EliminationByShrinking(deltaTimeSeconds);

    modelMatrix = visMatrix;
    
    modelMatrix *= transform2D::Translate(mousePositionX, 720 - mousePositionY);
    modelMatrix *= transform2D::Scale(weaponScale, weaponScale);
    RenderMesh2D(meshes[drawWeaponbyColor +"Weapon"], shaders["VertexColor"], modelMatrix);

    /*if (dropTimer > 8.0) {
        moneyStarsY -= 30 * deltaTimeSeconds;
    }
    else {
        dropTimer = 10.0f;
    }*/

    RenderMoneyStars(deltaTimeSeconds);

    /*Heart heart("redCircle", -5.0, 5.0, 5.0);
    AddMeshToList(object2D::CreateCircle("leftCircle", -4.7, 3.0, 5.0, glm::vec3(1, 0, 0), true));
    AddMeshToList(object2D::CreateCircle("rightCircle", 4.7, 3.0, 5.0, glm::vec3(1, 0, 0), true));
    AddMeshToList(object2D::CreateHeart("heart", glm::vec3(1, 0, 0), true));
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(900, 200);
    modelMatrix *= transform2D::Scale(10.0, 10.0);
    RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);*/
    //angle += deltaTimeSeconds;
    //RenderBullet(50 * deltaTimeSeconds, angle);
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    /*if (window->KeyHold(GLFW_KEY_W)) {
        drawWeaponbyColor = "purpleWeapon";
    }*/
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
    /*if (key == GLFW_KEY_W) {
        drawWeaponbyColor = "";
    }*/

}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
        mousePositionX = mouseX;
        mousePositionY = mouseY;
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1) {
        /*for (int i = 0; i < moneyStarsArray.size(); i++) {
            if (mouseX >= moneyStarsArray[i].getPosX() - 15
                && mouseX <= moneyStarsArray[i].getPosX() + 15
                && mouseY <= 720 - (moneyStarsArray[i].getPosY() - 15)
                && mouseY >= 720 - (moneyStarsArray[i].getPosY() + 15)) {
                moneyStarsToEliminate.push_back(moneyStarsArray[i]);
                moneyStarsArray.erase(moneyStarsArray.begin() + i);
                gameMoney++;
            }
        }*/
        for (auto money = moneyStarsArray.begin(); money != moneyStarsArray.end();) {
            if (mouseX >= money->getPosX() - 15
                && mouseX <= money->getPosX() + 15
                && mouseY <= 720 - (money->getPosY() - 15)
                && mouseY >= 720 - (money->getPosY() + 15)) {
                moneyStarsToEliminate.push_back(*money);
                money = moneyStarsArray.erase(money);
                gameMoney++;
            }
            else {
                ++money;
            }
        }
        if (mouseX >= 25 + (0 * 2 * 75) && mouseX <= 25 + (0 * 2 * 75) + 100 && mouseY <= 720 - 600 && mouseY >= 720 - 700) {
            if (gameMoney >= 1) drawWeaponbyColor = "orange";
        }
        else {
            if (mouseX >= 25 + (1 * 2 * 75) && mouseX <= 25 + (1 * 2 * 75) + 100 && mouseY <= 720 - 600 && mouseY >= 720 - 700) {
                if (gameMoney >= 2) drawWeaponbyColor = "blue";
            }
            else {
                if (mouseX >= 25 + (2 * 2 * 75) && mouseX <= 25 + (2 * 2 * 75) + 100 && mouseY <= 720 - 600 && mouseY >= 720 - 700) {
                    if (gameMoney >= 3) drawWeaponbyColor = "yellow";
                }
                else {
                    if (mouseX >= 25 + (3 * 2 * 75) && mouseX <= 25 + (3 * 2 * 75) + 100 && mouseY <= 720 - 600 && mouseY >= 720 - 700) {
                        if (gameMoney >= 4) drawWeaponbyColor = "purple";
                    }
                }
            }
        }
    }

    if (button == 2) {
        float objectPositionX = 0.0f, objectPositionY = 0.0f;
        if (mouseX >= 75 + (0 * 2 * 75) && mouseX <= 75 + (0 * 2 * 75) + 100) {
            objectPositionX = 75 + (0 * 2 * 75);
        }
        else {
            if (mouseX >= 75 + (1 * 2 * 75) && mouseX <= 75 + (1 * 2 * 75) + 100) {
                objectPositionX = 75 + (1 * 2 * 75);
            }
            else {
                if (mouseX >= 75 + (2 * 2 * 75) && mouseX <= 75 + (2 * 2 * 75) + 100) {
                    objectPositionX = 75 + (2 * 2 * 75);
                }
            }
        }

        if (mouseY <= 720 - (25 + (0 % 3 * 140)) && mouseY >= 720 - (25 + (0 % 3 * 140) + 100)) {
            objectPositionY = (25 + (0 % 3 * 140));
        }
        else {
            if (mouseY <= 720 - (25 + (1 % 3 * 140)) && mouseY >= 720 - (25 + (1 % 3 * 140) + 100)) {
                objectPositionY = (25 + (1 % 3 * 140));
            }
            else {
                if (mouseY <= 720 - (25 + (2 % 3 * 140)) && mouseY >= 720 - (25 + (2 % 3 * 140) + 100)) {
                    objectPositionY = (25 + (2 % 3 * 140));
                }
            }
        }

        if (objectPositionX != 0.0f && objectPositionY != 0.0f) {
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
    }
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 1) {
        float generateObjectX = 0.0f, generateObjectY = 0.0f;
        if (mouseX >= 75 + (0 * 2 * 75) && mouseX <= 75 + (0 * 2 * 75) + 100) {
            generateObjectX = 75 + (0 * 2 * 75);
        }
        else {
            if (mouseX >= 75 + (1 * 2 * 75) && mouseX <= 75 + (1 * 2 * 75) + 100) {
                generateObjectX = 75 + (1 * 2 * 75);
            }
            else {
                if (mouseX >= 75 + (2 * 2 * 75) && mouseX <= 75 + (2 * 2 * 75) + 100) {
                    generateObjectX = 75 + (2 * 2 * 75);
                }
            }
        }

        if (mouseY <= 720 - (25 + (0 % 3 * 140)) && mouseY >= 720 - (25 + (0 % 3 * 140) + 100)) {
            generateObjectY = (25 + (0 % 3 * 140));
        }
        else {
            if (mouseY <= 720 - (25 + (1 % 3 * 140)) && mouseY >= 720 - (25 + (1 % 3 * 140) + 100)) {
                generateObjectY = (25 + (1 % 3 * 140));
            }
            else {
                if (mouseY <= 720 - (25 + (2 % 3 * 140)) && mouseY >= 720 - (25 + (2 % 3 * 140) + 100)) {
                    generateObjectY = (25 + (2 % 3 * 140));
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
                Weapon weapon(id, drawWeaponbyColor, generateObjectX, generateObjectY, weaponScale, 5 * weaponScale);
                weapon.lastUpdateTime = std::chrono::high_resolution_clock::now();
                weapon.renderBullet = true;
                weaponArray.push_back(weapon);
                SpendMoney();
                //cout << drawWeaponbyColor << endl;
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




void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}

void Lab3::GetTime(float deltaTimeSeconds) {
    generateEnemycurrentTime = std::chrono::high_resolution_clock::now();
    elapsedEnemyTime = std::chrono::duration_cast<std::chrono::seconds>(generateEnemycurrentTime - generateEnemyLastUpdateTime);

    generateStarcurrentTime = generateEnemycurrentTime;
    elapsedStarTime = std::chrono::duration_cast<std::chrono::seconds>(generateStarcurrentTime - generateStarLastUpdateTime);

    generateBulletcurrentTime = generateEnemycurrentTime;
    elapsedBulletTime = std::chrono::duration_cast<std::chrono::seconds>(generateBulletcurrentTime - generateBulletLastUpdateTime);

    if (elapsedEnemyTime >= std::chrono::seconds(8)) {
        generateEnemyLastUpdateTime = generateEnemycurrentTime;
        addEnemy = true;
    }

    if (elapsedStarTime >= std::chrono::seconds(3)) {
        generateStarLastUpdateTime = generateStarcurrentTime;
        generateStarsBool = true;
        //RenderMoneyStars(deltaTimeSeconds);
        moneyStarsY = 700.0f;
    }
    for (auto weapon = weaponArray.begin(); weapon != weaponArray.end();) {
        weapon->currentTime = std::chrono::high_resolution_clock::now();
        weapon->elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(weapon->currentTime - weapon->lastUpdateTime);
        if (weapon->elapsedTime >= std::chrono::seconds(2)) {
            weapon->lastUpdateTime = weapon->currentTime;
            weapon->renderBullet = true;
        }
        ++weapon;
    }
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

    AddMeshToList(object2D::CreateSquare("redSquare", glm::vec3(1, 0, 0), true));

    AddMeshToList(object2D::CreateSquare("greenSquare", glm::vec3(0, 1, 0), true));

    AddMeshToList(object2D::CreateSquare("blueSquare", glm::vec3(0, 0, 1), true));

    AddMeshToList(object2D::CreateSquare("orangeSquare", glm::vec3(1, 0.5, 0), true));

    AddMeshToList(object2D::CreateSquare("yellowSquare", glm::vec3(1, 1, 0), true));

    AddMeshToList(object2D::CreateSquare("purpleSquare", glm::vec3(0.5, 0, 0.5), true));

    AddMeshToList(object2D::CreateSquare("witeSquare", glm::vec3(1, 1, 1)));
}

void Lab3::InitWeapons()
{
    // Define weapons
    weaponCollorArray[0] = "orangeWeapon";
    weaponCollorArray[1] = "blueWeapon";
    weaponCollorArray[2] = "yellowWeapon";
    weaponCollorArray[3] = "purpleWeapon";
    weaponCollorArray[4] = "redWeapon";

    AddMeshToList(object2D::CreateWeapon("redWeapon", corner, squareSide, glm::vec3(1, 0, 0), true));

    AddMeshToList(object2D::CreateWeapon("blueWeapon", corner, squareSide, glm::vec3(0, 0, 1), true));

    AddMeshToList(object2D::CreateWeapon("orangeWeapon", corner, squareSide, glm::vec3(1, 0.5, 0), true));

    AddMeshToList(object2D::CreateWeapon("yellowWeapon", corner, squareSide, glm::vec3(1, 1, 0), true));

    AddMeshToList(object2D::CreateWeapon("purpleWeapon", corner, squareSide, glm::vec3(0.5, 0, 0.5), true));

    AddMeshToList(object2D::CreateWeapon("whiteWeapon", corner, squareSide, glm::vec3(1, 1, 1), true));
}

void Lab3::InitStars()
{
    // Define stars
    starCollorArray[0] = "orangeStar";
    starCollorArray[1] = "blueStar";
    starCollorArray[2] = "yellowStar";
    starCollorArray[3] = "purpleStar";
    starCollorArray[4] = "redStar";

    AddMeshToList(object2D::CreateStar("redStar", corner, squareSide, glm::vec3(1, 0, 0), true));

    AddMeshToList(object2D::CreateStar("blueStar", corner, squareSide, glm::vec3(0, 0, 1), true));

    AddMeshToList(object2D::CreateStar("orangeStar", corner, squareSide, glm::vec3(1, 0.5, 0), true));

    AddMeshToList(object2D::CreateStar("yellowStar", corner, squareSide, glm::vec3(1, 1, 0), true));

    AddMeshToList(object2D::CreateStar("purpleStar", corner, squareSide, glm::vec3(0.5, 0, 0.5), true));

    AddMeshToList(object2D::CreateStar("whiteStar", corner, squareSide, glm::vec3(1, 1, 1), true));
}

void Lab3::InitHexagons()
{
    // Define stars
    hexagonCollorArray[0] = "orangeHexagon";
    hexagonCollorArray[1] = "blueHexagon";
    hexagonCollorArray[2] = "yellowHexagon";
    hexagonCollorArray[3] = "purpleHexagon";

    AddMeshToList(object2D::CreateHexagon("redHexagon", corner, squareSide, glm::vec3(1, 0, 0), true));

    AddMeshToList(object2D::CreateHexagon("blueHexagon", corner, squareSide, glm::vec3(0, 0, 1), true));

    AddMeshToList(object2D::CreateHexagon("orangeHexagon", corner, squareSide, glm::vec3(1, 0.5, 0), true));

    AddMeshToList(object2D::CreateHexagon("yellowHexagon", corner, squareSide, glm::vec3(1, 1, 0), true));

    AddMeshToList(object2D::CreateHexagon("purpleHexagon", corner, squareSide, glm::vec3(0.5, 0, 0.5), true));

    AddMeshToList(object2D::CreateHexagon("whiteHexagon", corner, squareSide, glm::vec3(1, 1, 1), true));
}


void Lab3::RenderArenaSquares()
{

    modelMatrix = visMatrix;
    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << modelMatrix[i][j] << " ";
        }
        cout << endl;
    }*/
    //cout << modelMatrix << endl;
    modelMatrix *= transform2D::Translate(30, 215);
    modelMatrix *= transform2D::Scale(2, 20);
    RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            modelMatrix = visMatrix;
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
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Translate(800 + (i * 2 * 60), 600);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::RenderAvaibleWeapons()
{
    int translateX, translateY;
    for (int i = 0; i < 4; i++) {
        translateX = 25 + (i * 2 * 75);
        translateY = 600;
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Scale(5, 5);
        RenderMesh2D(meshes["witeSquare"], shaders["VertexColor"], modelMatrix);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(squareSide / 2, squareSide / 2);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Scale(weaponScale, weaponScale);
        RenderMesh2D(meshes[weaponCollorArray[i]], shaders["VertexColor"], modelMatrix);
        for (int j = 0; j < (i + 1) % 5; j++) {
            RenderPriceStars(translateX + j * 30, translateY);
        }
    }
}

void Lab3::RenderPriceStars(int translateX, int translateY)
{
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(translateX + 9, translateY - 25);
        modelMatrix *= transform2D::Scale(1.5, 1.5);
        RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
}

void Lab3::RenderAvaibleMoney()
{
    
    for (int i = 0; i < gameMoney; i++) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(800 + i * 30, 575);
        modelMatrix *= transform2D::Scale(1.5, 1.5);

        RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
    }
    
    
}
 
void Lab3::RenderWeapon(float deltaTime)
{
    for (int i = 0; i < weaponArray.size(); i++) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(weaponArray[i].getPosX(), weaponArray[i].getPosY());
        modelMatrix *= transform2D::Scale(weaponArray[i].getSize(), weaponArray[i].getSize());
        RenderMesh2D(meshes[weaponArray[i].getColor() + "Weapon"], shaders["VertexColor"], modelMatrix);
        /*glm::vec3 originalPosition(0.0f, 0.0f, 0.0f);
        glm::vec3 newPosition = enemyArray[i].getMatrix() * originalPosition;
        cout << "x = " << newPosition.x << endl;*/
    }
}

void Lab3::RenderEnemy(float deltaTime)
{
    if (addEnemy == true) {
        addEnemy = false;
        AddEnemyInGame();
    }
    //for (int i = 0; i < enemyArray.size(); i++) {
    //    modelMatrix = visMatrix;
    //    modelMatrix *= transform2D::Translate(enemyArray[i].getPosX() - 50 * deltaTime, enemyArray[i].getPosY());
    //    modelMatrix *= transform2D::Scale(enemyArray[i].getSize(), enemyArray[i].getSize());

    //    enemyArray[i].setPosX(enemyArray[i].getPosX() - 50 * deltaTime);
    //    if (enemyArray[i].getPosX() <= 75.0f) {
    //        playerHealt -= 1;
    //        enemiesToEliminate.push_back(enemyArray[i]);
    //        enemyArray.erase(enemyArray.begin() + i);
    //    }
    //    else {
    //        RenderMesh2D(meshes[enemyArray[i].getColor() + "Hexagon"], shaders["VertexColor"], modelMatrix);
    //    }
    //    /*glm::vec3 originalPosition(0.0f, 0.0f, 0.0f);
    //    glm::vec3 newPosition = enemyArray[i].getMatrix() * originalPosition;
    //    cout << "x = " << newPosition.x << endl;*/
    //}

    for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
        
        if (enemy->getPosX() <= 75.0f) {
            playerHealt -= 1;
            enemiesToEliminate.push_back(*enemy);
            enemy = enemyArray.erase(enemy);
        }
        else {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(enemy->getPosX() - 50 * deltaTime, enemy->getPosY());
            modelMatrix *= transform2D::Scale(enemy->getSize(), enemy->getSize());

            enemy->setPosX(enemy->getPosX() - 100 * deltaTime);
            RenderMesh2D(meshes[enemy->getColor() + "Hexagon"], shaders["VertexColor"], modelMatrix);
            ++enemy;
        }
    }
}


void Lab3::AddEnemyInGame() {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution1(0, 1000);
    randomObject = distribution1(generator) % 4;
    std::uniform_int_distribution<int> distribution2(0, 1000);
    randomPosition = distribution2(generator) % 3;
    glm::mat3 enemyMatrix = visMatrix;
    enemyMatrix *= transform2D::Translate(1200.0f, 75.0f + (randomPosition % 3 * 140));
    enemyMatrix *= transform2D::Scale(3.0f, 3.0f);


    std::string color = hexagonCollorArray[randomObject];
    size_t pos = color.find("Hexagon");
    color.erase(pos, 7);
    Enemy enemy(id, color, 1200.0f, 75.0f + (randomPosition % 3 * 140), 3.0f, enemyMatrix);
    enemy.setRadius(enemy.getRadius() * 3.0f);
    id++;
    enemyArray.push_back(enemy);
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
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(enemy->getPosX(), enemy->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            enemy->setSize(size);
            RenderMesh2D(meshes[enemy->getColor() + "Hexagon"], shaders["VertexColor"], modelMatrix);
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
            modelMatrix = visMatrix;
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
            modelMatrix = visMatrix;
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
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(bullet->getPosX(), bullet->getPosY());
            modelMatrix *= transform2D::Scale(size, size);
            bullet->setSize(size);
            RenderMesh2D(meshes[bullet->getColor() + "Star"], shaders["VertexColor"], modelMatrix);
            ++bullet;
        }
    }
}

void Lab3::RenderBullet(float deltaTimeSecond, float angle)
{


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
        if (genBullet == true) {
            Bullet bullet(id, weapon->getColor(), weapon->getPosX() + 20.0f, weapon->getPosY(), 3.0f, 0.0f);
            bullet.setRadius(bullet.getRadius() * 3.0f);
            bulletArray.push_back(bullet);
        }
        ++weapon;
    }





    /*if (generateBulletBool == true) {
        generateBulletBool = false;
        for (int i = 0; i < weaponArray.size(); i++) {
            for (int j = 0; j < enemyArray.size(); j++) {
                if (weaponArray[i].getPosY() == enemyArray[j].getPosY() && weaponArray[i].getColor() == enemyArray[j].getColor()) {
                    Bullet bullet(id, weaponArray[i].getColor(), weaponArray[i].getPosX() + 20.0f, weaponArray[i].getPosY(), 3.0f, 0.0f);
                    bullet.setRadius(bullet.getRadius() * 3.0f);
                    bulletArray.push_back(bullet);
                }
            }
        }
    }*/
    /*bool bulletElimination = false;
    for (auto bullet = bulletArray.begin(); bullet != bulletArray.end();) {
        bulletElimination = false;
        for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
            CheckWeaponEnemyColision(enemy);
            if (bullet->getPosY() == enemy->getPosY() && bullet->getColor() == enemy->getColor()) {
                if ((enemy->getPosX() > bullet->getPosX()) && (enemy->getPosX() - bullet->getPosX() <= enemy->getRadius() + bullet->getRadius())) {
                    bulletElimination = true;
                    enemy->setHealt(enemy->getHealt() - 1);
                    if (enemy->getHealt() == 0) {
                        if (enemy->getColor() == "orange" || enemy->getColor() == "blue") gameMoney += 2;
                        if (enemy->getColor() == "yellow" || enemy->getColor() == "purple") gameMoney += 3;
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
            else {
                ++enemy;
            }
        }
        if (bulletElimination == true) {
            bulletToEliminate.push_back(*bullet);
            bullet = bulletArray.erase(bullet);
        }
        else {
            ++bullet;
        }
    }*/

    bool enemyElimination = false;
    for (auto enemy = enemyArray.begin(); enemy != enemyArray.end();) {
        enemyElimination = false;
        CheckWeaponEnemyColision(enemy);
        enemyElimination = CheckBulletEnemyColision(enemy);
        /*for (auto bullet = bulletArray.begin(); bullet != bulletArray.end();) {
            if (bullet->getPosY() == enemy->getPosY() && bullet->getColor() == enemy->getColor()) {
                if ((enemy->getPosX() > bullet->getPosX()) && (enemy->getPosX() - bullet->getPosX() <= enemy->getRadius() + bullet->getRadius())) {
                    bulletToEliminate.push_back(*bullet);
                    bullet = bulletArray.erase(bullet);
                    enemyElimination = true;
                }
                else {
                    ++bullet;
                }
            }
            else {
                ++bullet;
            }
        }*/
        if (enemyElimination == true) {
            enemy->setHealt(enemy->getHealt() - 1);
            if (enemy->getHealt() == 0) {
                if (enemy->getColor() == "orange" || enemy->getColor() == "blue") gameMoney += 2;
                if (enemy->getColor() == "yellow" || enemy->getColor() == "purple") gameMoney += 3;
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

    for (auto bullet = bulletArray.begin(); bullet != bulletArray.end();) {

        if (bullet->getPosX() > 1200) {
            bulletToEliminate.push_back(*bullet);
            bullet = bulletArray.erase(bullet);
        }
        else {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(bullet->getPosX(), bullet->getPosY());
            modelMatrix *= transform2D::Scale(bullet->getSize(), bullet->getSize());
            modelMatrix *= transform2D::Rotate(-bullet->getAngle());
            RenderMesh2D(meshes[bullet->getColor() + "Star"], shaders["VertexColor"], modelMatrix);
            bullet->setPosX(bullet->getPosX() + 200 * deltaTimeSecond);
            bullet->setAngle(bullet->getAngle() + 3 * deltaTimeSecond);
            ++bullet;
        }
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

bool Lab3::CheckBulletEnemyColision(std::vector<Enemy>::iterator enemy)
{
    bool enemyElimination = false;
    for (auto bullet = bulletArray.begin(); bullet != bulletArray.end();) {
        if (bullet->getPosY() == enemy->getPosY() && bullet->getColor() == enemy->getColor()) {
            if ((enemy->getPosX() > bullet->getPosX()) && (enemy->getPosX() - bullet->getPosX() <= enemy->getRadius() + bullet->getRadius())) {
                bulletToEliminate.push_back(*bullet);
                bullet = bulletArray.erase(bullet);
                enemyElimination = true;
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


void Lab3::RenderMoneyStars(float deltaTimeSecond)
{
    dropTimer -= 10 * deltaTimeSecond;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution1(50, 1200);

    if (generateStarsBool == true) {
        generateStarsBool = false;
        int xPos = distribution1(generator);
        MoneyStars moneyStar("purpleStar", xPos, 600, 3.0f);
        moneyStarsArray.push_back(moneyStar);
    }

    for (auto money = moneyStarsArray.begin(); money != moneyStarsArray.end();) {
        if (money->getPosY() <= 5) {
            //moneyStarsToEliminate.push_back(money);
            moneyStarsToEliminate.push_back(*money);
            money = moneyStarsArray.erase(money);
        }
        else {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(money->getPosX(), money->getPosY());
            modelMatrix *= transform2D::Scale(money->getSize(), money->getSize());
            RenderMesh2D(meshes["purpleStar"], shaders["VertexColor"], modelMatrix);
            money->setPosY(money->getPosY() - 30 * deltaTimeSecond);
            ++money;
        }
        
    }

}
