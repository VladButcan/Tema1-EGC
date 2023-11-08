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
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    corner = glm::vec3(0, 0, 0);
    squareSide = 100;
    

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    
    angularStep = 0;
    InitSquares();
    InitWeapons();
    InitStars();
    /*Mesh* blockSquare = object2D::CreateTransparentSquare("blockSquare", corner, squareSide, glm::vec4(1, 1, 1, 0.1f));
    AddMeshToList(blockSquare);*/

    Mesh* triangle = object2D::CreateTriangle("triangle", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(triangle);

    Mesh* hexagon = object2D::CreateHexagon("hexagon", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(hexagon);

    //Mesh* star = object2D::CreateStar("star", corner, squareSide, glm::vec3(1, 0, 0), true);
    //AddMeshToList(star);

    /*Mesh* weapon = object2D::CreateWeapon("weapon", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(weapon);*/
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    RenderArena();
    RenderHealt();
    RenderWeapons();
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 25);
    RenderMesh2D(meshes["hexagon"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(650, 75);
    modelMatrix *= transform2D::Scale(0.8, 0.8);
    modelMatrix *= transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["hexagon"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(900, 25);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    clock += deltaTimeSeconds;
    if (clock >= 3) {
        clock = 0;
        addEnemy = true;
    }
    RenderEnemy();


    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(900, 25);
    RenderMesh2D(meshes["weapon"], shaders["VertexColor"], modelMatrix);*/

    /*for (int i = 0; i < 6; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(800, 200);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        modelMatrix *= transform2D::Rotate(3.14 * 2 / 6 * i);
        modelMatrix *= transform2D::Translate(-50, -13);
        modelMatrix *= transform2D::Translate(50, 50);
        modelMatrix *= transform2D::Rotate(3.14);
        modelMatrix *= transform2D::Translate(-50, -50);
        RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);
    }*/
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
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
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

    AddMeshToList(object2D::CreateSquare("redSquare", corner, squareSide, glm::vec3(1, 0, 0), true));

    AddMeshToList(object2D::CreateSquare("greenSquare", corner, squareSide, glm::vec3(0, 1, 0), true));

    AddMeshToList(object2D::CreateSquare("blueSquare", corner, squareSide, glm::vec3(0, 0, 1), true));

    AddMeshToList(object2D::CreateSquare("orangeSquare", corner, squareSide, glm::vec3(1, 0.5, 0), true));

    AddMeshToList(object2D::CreateSquare("yellowSquare", corner, squareSide, glm::vec3(1, 1, 0), true));

    AddMeshToList(object2D::CreateSquare("purpleSquare", corner, squareSide, glm::vec3(0.5, 0, 0.5), true));

    AddMeshToList(object2D::CreateSquare("witeSquare", corner, squareSide, glm::vec3(1, 1, 1)));
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


void Lab3::RenderArena()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 25);
    modelMatrix *= transform2D::Scale(0.5, 4);
    RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(75 + (j * 2 * 75), 25 + (i % 3 * 140));
            modelMatrix *= transform2D::Scale(1.2, 1.2);
            RenderMesh2D(meshes["greenSquare"], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Lab3::RenderHealt()
{
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(800 + (i * 2 * 60), 600);
        RenderMesh2D(meshes["redSquare"], shaders["VertexColor"], modelMatrix);
    }
}


void Lab3::RenderWeapons()
{
    int translateX, translateY;
    for (int i = 0; i < 4; i++) {
        translateX = 25 + (i * 2 * 75);
        translateY = 600;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes["witeSquare"], shaders["VertexColor"], modelMatrix);

        modelMatrix *= transform2D::Translate(15,10);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes[weaponCollorArray[i]], shaders["VertexColor"], modelMatrix);
        for (int j = 0; j < (i + 1) % 5; j++) {
            RenderStar(translateX + j * 30, translateY);
        }
    }
}

void Lab3::RenderStar(int translateX, int translateY)
{
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY - 25);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
}

void Lab3::RenderEnemy()
{
    if (addEnemy == true) {
        addEnemy = false;
        std::uniform_int_distribution<int> distribution(0, 4);
        randomNumber = distribution(generator);
        enemyArray.push_back(hexagonCollorArray[randomNumber]);
    }
    for (int i = 0; i < enemyArray.size(); i++) {

    }
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY - 25);
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    RenderMesh2D(meshes["whiteStar"], shaders["VertexColor"], modelMatrix);
}

//void Lab3::RenderBlockSquare(int translateX, int translateY)
//{
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(translateX, translateY);
//    RenderMesh2D(meshes["blockSquare"], shaders["VertexColor"], modelMatrix);
//}

//Mesh* Lab3::RenderWeapon(float R, float G, float B)
//{
//
//}
