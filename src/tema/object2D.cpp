#include "object2D.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-10, -10, 0), color),
        VertexFormat(glm::vec3(10 , -10, 0), color),
        VertexFormat(glm::vec3(10 , 10 , 0), color),
        VertexFormat(glm::vec3(-10, 10 , 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    // Define the points for the hexagon
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-6, -10.4, 0), color),
        VertexFormat(glm::vec3(6 , -10.4, 0), color),
        VertexFormat(glm::vec3(12, 0    , 0), color),
        VertexFormat(glm::vec3(6 , 10.4 , 0), color),
        VertexFormat(glm::vec3(-6, 10.4 , 0), color),
        VertexFormat(glm::vec3(-12, 0   , 0), color)
    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
        // Define indices for the lines that form the hexagon
        indices = { 0, 1, 2, 3, 4, 5 };
    }
    else {
        // Define indices to create triangles that fill the hexagon
        indices = { 0, 1, 4, 1, 2, 4, 2, 3, 4, 5, 0, 4};
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}


Mesh* object2D::CreateWeapon(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-5, 0, 0), color),
        VertexFormat(glm::vec3(0, -10, 0), color),
        VertexFormat(glm::vec3(5, 0, 0), color),
        VertexFormat(glm::vec3(0, 10, 0), color),
        VertexFormat(glm::vec3(3.5, 3, 0), color),
        VertexFormat(glm::vec3(10, 3, 0), color),
        VertexFormat(glm::vec3(10, -3, 0), color),
        VertexFormat(glm::vec3(3.5, -3, 0), color)
    };

    Mesh* weapon = new Mesh(name);
    std::vector<unsigned int> indices;
    if (!fill) {
        weapon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices = { 0, 1, 2, 3, 0, 2, 4, 5, 2, 5, 6, 2, 6, 7, 2};
    }

    weapon->InitFromData(vertices, indices);
    return weapon;
}

Mesh* object2D::CreateStar(
const std::string& name,
glm::vec3 color,
bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-9.546, 2.125 , 0), color),
        VertexFormat(glm::vec3(9.546 , 2.125 , 0), color),
        VertexFormat(glm::vec3(0, -4.81, 0), color),
        VertexFormat(glm::vec3(-3.64, -2.16, 0), color),
        VertexFormat(glm::vec3(5.9, -9.097, 0), color),
        VertexFormat(glm::vec3(0, 9.061, 0), color),
        VertexFormat(glm::vec3(-5.9, -9.097, 0), color),
        VertexFormat(glm::vec3(3.646, -2.161, 0), color)
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices;
    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices = { 0, 1, 2, 0, 2, 3, 4, 5, 3, 5, 6, 7, 5, 6, 7};
    }

    star->InitFromData(vertices, indices);
    return star;
}


Mesh* object2D::CreateCircle(
    const std::string& name,
    float centerX,
    float centerY,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    int numOfVertices = 30;
    for (int i = 0; i < numOfVertices; ++i) {
        float theta = 2.0f * 3.14 * i / static_cast<float>(numOfVertices);
        float x = centerX + radius * std::cos(theta);
        float y = centerY + radius * std::sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }
    vertices.push_back(VertexFormat(glm::vec3(centerX, centerY, 0), color));

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < numOfVertices - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(numOfVertices);
    }
    indices.push_back(numOfVertices - 1);
    indices.push_back(0);
    indices.push_back(numOfVertices);
    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}


Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    int numOfVertices = 30;
    for (int i = 0; i < numOfVertices; ++i) {
        float theta = 2.0f * 3.14 * i / numOfVertices;
        float x = 4.7 + 5.0 * std::cos(theta);
        float y = 3 + 5.0 * std::sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }
    vertices.push_back(VertexFormat(glm::vec3(5, 3, 0), color));

    vertices.push_back(VertexFormat(glm::vec3(-5, 3, 0), color));
    for (int i = 0; i < numOfVertices; ++i) {
        float theta = 2.0f * 3.14 * i / numOfVertices;
        float x = -4.7 + 5.0 * std::cos(theta);
        float y = 3 + 5.0 * std::sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    vertices.push_back(VertexFormat(glm::vec3(-8, -0.9, 0), color));
    vertices.push_back(VertexFormat(glm::vec3(0, -8, 0), color));
    vertices.push_back(VertexFormat(glm::vec3(8, -0.9, 0), color));

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < numOfVertices - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(numOfVertices);
    }
    indices.push_back(numOfVertices - 1);
    indices.push_back(0);
    indices.push_back(numOfVertices);
    indices.push_back(numOfVertices + 1);



    for (int i = numOfVertices + 2; i < 2 * numOfVertices + 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(numOfVertices + 1);
    }
    indices.push_back(2 * numOfVertices + 1);
    indices.push_back(numOfVertices + 2);
    indices.push_back(numOfVertices + 1);
    

    indices.push_back(2 * numOfVertices + 2);
    indices.push_back(2 * numOfVertices + 3);
    indices.push_back(numOfVertices + 1);
    indices.push_back(2 * numOfVertices + 3);
    indices.push_back(2 * numOfVertices + 4);


    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    }

    heart->InitFromData(vertices, indices);
    return heart;
}


Mesh* object2D::CreateZero(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-8, 8, 0), color),
        VertexFormat(glm::vec3(-4, 12, 0), color),
        VertexFormat(glm::vec3(4, 12, 0), color),
        VertexFormat(glm::vec3(8, 8, 0), color),
        VertexFormat(glm::vec3(8, -8, 0), color),
        VertexFormat(glm::vec3(4, -12, 0), color),
        VertexFormat(glm::vec3(-4, -12, 0), color),
        VertexFormat(glm::vec3(-8, -8, 0), color),
        VertexFormat(glm::vec3(-4, 6, 0), color),
        VertexFormat(glm::vec3(-2, 8, 0), color),
        VertexFormat(glm::vec3(2, 8, 0), color),
        VertexFormat(glm::vec3(4, 6, 0), color),
        VertexFormat(glm::vec3(4, -6, 0), color),
        VertexFormat(glm::vec3(2, -8, 0), color),
        VertexFormat(glm::vec3(-2, -8, 0), color),
        VertexFormat(glm::vec3(-4, -6, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 9, 8, 0, 9,
    9, 10, 2, 1, 9, 2,
    2, 3, 11, 10, 2, 11,
    11, 12, 4, 3, 11, 4,
    4, 5, 13, 12, 4, 13,
    13, 14, 6, 5, 13, 6,
    6, 7, 15, 14, 6, 15,
    15, 8, 0, 7, 15, 0};

    number->InitFromData(vertices, indices);
    return number;
}


Mesh* object2D::CreateOne(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-5, 8, 0), color),
        VertexFormat(glm::vec3(-5, 10, 0), color),
        VertexFormat(glm::vec3(-2, 12, 0), color),
        VertexFormat(glm::vec3(2, 12, 0), color),
        VertexFormat(glm::vec3(2, -9, 0), color),
        VertexFormat(glm::vec3(5, -9, 0), color),
        VertexFormat(glm::vec3(5, -12, 0), color),
        VertexFormat(glm::vec3(-5, -12, 0), color),
        VertexFormat(glm::vec3(-5, -9, 0), color),
        VertexFormat(glm::vec3(-2, -9, 0), color),
        VertexFormat(glm::vec3(-2, 8, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    //weapon->SetDrawMode(GL_LINE_LOOP);
    indices = { 0, 1, 2, 10, 0, 2, 2, 3, 4, 9, 2, 4, 5, 6, 7, 8, 5, 7 };

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateTwo(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-8, 6, 0), color),
        VertexFormat(glm::vec3(-8, 8, 0), color),
        VertexFormat(glm::vec3(-4, 12, 0), color),
        VertexFormat(glm::vec3(4, 12, 0), color),
        VertexFormat(glm::vec3(8, 8, 0), color),
        VertexFormat(glm::vec3(8, 2, 0), color),
        VertexFormat(glm::vec3(-4, -8, 0), color),
        VertexFormat(glm::vec3(4, -8, 0), color),
        VertexFormat(glm::vec3(4, -7, 0), color),
        VertexFormat(glm::vec3(8, -7, 0), color),
        VertexFormat(glm::vec3(8, -12, 0), color),
        VertexFormat(glm::vec3(-8, -12, 0), color),
        VertexFormat(glm::vec3(-8, -6, 0), color),
        VertexFormat(glm::vec3(4, 4, 0), color),
        VertexFormat(glm::vec3(4, 7, 0), color),
        VertexFormat(glm::vec3(3, 8, 0), color),
        VertexFormat(glm::vec3(-3, 8, 0), color),
        VertexFormat(glm::vec3(-4, 7, 0), color),
        VertexFormat(glm::vec3(-4, 6, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 17, 18, 0, 17
                , 17, 1, 2, 16, 17, 2
                , 2, 16, 15, 3, 2, 15
                , 15, 3, 4, 14, 15, 4
                , 4, 5, 13, 14, 4, 13
                , 13, 5, 6, 12, 13, 6
                , 11, 12, 6, 12, 11, 6
                , 6, 11, 10, 7, 6, 10
                , 10, 9, 8, 7, 10, 8};

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateThree(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-7, 6, 0), color),
        VertexFormat(glm::vec3(-7, 9, 0), color),
        VertexFormat(glm::vec3(-4, 12, 0), color),
        VertexFormat(glm::vec3(5, 12, 0), color),
        VertexFormat(glm::vec3(8, 9, 0), color),
        VertexFormat(glm::vec3(8, 1, 0), color),
        VertexFormat(glm::vec3(7, 0, 0), color),
        VertexFormat(glm::vec3(8, -1, 0), color),
        VertexFormat(glm::vec3(8, -9, 0), color),
        VertexFormat(glm::vec3(5, -12, 0), color),
        VertexFormat(glm::vec3(-4, -12, 0), color),
        VertexFormat(glm::vec3(-7, -9, 0), color),
        VertexFormat(glm::vec3(-7, -6, 0), color),//
        VertexFormat(glm::vec3(-3, -6, 0), color),
        VertexFormat(glm::vec3(-3, -7, 0), color),
        VertexFormat(glm::vec3(-2, -8, 0), color),
        VertexFormat(glm::vec3(3, -8, 0), color),
        VertexFormat(glm::vec3(4, -7, 0), color),
        VertexFormat(glm::vec3(4, -3, 0), color),
        VertexFormat(glm::vec3(3, -2, 0), color),
        VertexFormat(glm::vec3(-2, -2, 0), color),
        VertexFormat(glm::vec3(-2, 2, 0), color),
        VertexFormat(glm::vec3(3, 2, 0), color),
        VertexFormat(glm::vec3(4, 3, 0), color),
        VertexFormat(glm::vec3(4, 7, 0), color),
        VertexFormat(glm::vec3(3, 8, 0), color),
        VertexFormat(glm::vec3(-2, 8, 0), color),
        VertexFormat(glm::vec3(-3, 7, 0), color),
        VertexFormat(glm::vec3(-3, 6, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    //weapon->SetDrawMode(GL_LINE_LOOP);
    indices = { 0, 1, 27, 28, 0, 27
                , 27, 1, 2, 26, 27, 2
                , 2, 3, 25, 26, 2, 25
                , 25, 3, 4, 24, 25, 4
                , 4, 5, 23, 24, 4, 23
                , 23, 5, 6, 22, 23, 6
                , 6, 22, 19, 22, 6, 19
                , 19, 20, 21, 22, 19
                , 21, 19, 6, 7, 18, 19, 7
                , 7, 8, 17, 18, 7, 17
                , 17, 8, 9, 16, 17, 9
                , 9, 10, 15, 16, 9, 15
                , 15, 10, 11, 14, 15, 11
                , 11, 12, 13, 14, 11, 13};

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateFour(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-9, 0, 0), color),
        VertexFormat(glm::vec3(0, 12 , 0), color),
        VertexFormat(glm::vec3(6, 12, 0), color),
        VertexFormat(glm::vec3(6, -9, 0), color),
        VertexFormat(glm::vec3(9, -9, 0), color),
        VertexFormat(glm::vec3(9, -12, 0), color),
        VertexFormat(glm::vec3(-1, -12, 0), color),
        VertexFormat(glm::vec3(-1, -9, 0), color),
        VertexFormat(glm::vec3(2, -9, 0), color),
        VertexFormat(glm::vec3(2, 8, 0), color),
        VertexFormat(glm::vec3(-4, 0, 0), color),
        VertexFormat(glm::vec3(9, 0, 0), color),
        VertexFormat(glm::vec3(9, -4 , 0), color),
        VertexFormat(glm::vec3(-7, -4, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 9, 10, 0, 9
                , 9, 1, 2, 1, 9, 2
                , 2, 3, 8, 9, 2, 8
                , 8, 6, 7, 6, 8
                , 6, 5, 4, 8, 6, 5, 8
                , 10, 0, 13, 0, 10, 13
                , 13, 10, 11, 12, 13, 11 };

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateFive(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-8, -6 , 0), color),
        VertexFormat(glm::vec3(-8, -8, 0), color),
        VertexFormat(glm::vec3(-4, -12, 0), color),
        VertexFormat(glm::vec3(4, -12, 0), color),
        VertexFormat(glm::vec3(8, -8, 0), color),
        VertexFormat(glm::vec3(8, -1, 0), color),
        VertexFormat(glm::vec3(4, 3, 0), color),
        VertexFormat(glm::vec3(-2, 3, 0), color),
        VertexFormat(glm::vec3(-4, 5, 0), color),
        VertexFormat(glm::vec3(-4, 8, 0), color),
        VertexFormat(glm::vec3(8, 8, 0), color),
        VertexFormat(glm::vec3(8, 12, 0), color),
        VertexFormat(glm::vec3(-8, 12, 0), color),
        VertexFormat(glm::vec3(-8, 3, 0), color),
        VertexFormat(glm::vec3(-4, -1, 0), color),
        VertexFormat(glm::vec3(3, -1, 0), color),
        VertexFormat(glm::vec3(4, -2, 0), color),
        VertexFormat(glm::vec3(4, -7, 0), color),
        VertexFormat(glm::vec3(3, -8, 0), color),
        VertexFormat(glm::vec3(-2, -8, 0), color),
        VertexFormat(glm::vec3(-3, -7, 0), color),
        VertexFormat(glm::vec3(-3, -6, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 20, 21, 0, 20,
                20, 19, 2, 1, 20, 2,
                2, 3, 18, 19, 2, 18,
                18, 17, 4, 3, 18, 4,
                4, 5, 16, 17, 4, 16,
                16, 15, 6, 5, 16, 6,
                6, 7, 14, 15, 6, 14,
                14, 13, 8, 7, 14, 8,
                8, 9, 12, 13, 8, 12,
                12, 11, 10, 9, 12, 10};

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateSix(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(8, 6, 0), color),
        VertexFormat(glm::vec3(8, 9, 0), color),
        VertexFormat(glm::vec3(5, 12, 0), color),
        VertexFormat(glm::vec3(-4, 12, 0), color),
        VertexFormat(glm::vec3(-7, 9, 0), color),
        VertexFormat(glm::vec3(-7, -9, 0), color),
        VertexFormat(glm::vec3(-5, -12, 0), color),
        VertexFormat(glm::vec3(6, -12, 0), color),
        VertexFormat(glm::vec3(8, -9, 0), color),
        VertexFormat(glm::vec3(8, 0, 0), color),
        VertexFormat(glm::vec3(6, 3, 0), color),
        VertexFormat(glm::vec3(-3, 3, 0), color),
        VertexFormat(glm::vec3(-3, 8, 0), color),
        VertexFormat(glm::vec3(4, 8, 0), color),
        VertexFormat(glm::vec3(4, 6, 0), color),
        VertexFormat(glm::vec3(-3, -1, 0), color),
        VertexFormat(glm::vec3(4, -1, 0), color),
        VertexFormat(glm::vec3(4, -8, 0), color),
        VertexFormat(glm::vec3(-3, -8, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 13, 14, 0, 13,
                13, 1, 2, 1, 13, 2,
                2, 3, 12, 13, 2, 12,
                12, 3, 4, 3, 12, 4,
                4, 5, 18, 12, 4, 18,
                18, 5, 6, 5, 18, 6,
                6, 7, 17, 18, 6, 17,
                17, 7, 8, 7, 17, 8,
                8, 9, 16, 17, 8, 16,
                16, 9, 10, 9, 16, 10,
                10, 11, 15, 16, 10, 15 };

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateSeven(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-7, 6, 0), color),
        VertexFormat(glm::vec3(-7, 12, 0), color),
        VertexFormat(glm::vec3(8, 12, 0), color),
        VertexFormat(glm::vec3(8, 7, 0), color),
        VertexFormat(glm::vec3(0, -12, 0), color),
        VertexFormat(glm::vec3(-4, -12, 0), color),
        VertexFormat(glm::vec3(4, 8, 0), color),
        VertexFormat(glm::vec3(-3, 8, 0), color),
        VertexFormat(glm::vec3(-3, 6, 0), color),
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 7, 8, 0, 7,
                7, 6, 2, 1, 7, 2,
                2, 6, 3, 6, 2, 3,
                3, 4, 5, 6, 3, 5};

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateEight(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-4, 12, 0), color),
        VertexFormat(glm::vec3(4, 12, 0), color),
        VertexFormat(glm::vec3(7, 9, 0), color),
        VertexFormat(glm::vec3(7, 1, 0), color),
        VertexFormat(glm::vec3(6, 0, 0), color),
        VertexFormat(glm::vec3(7, -1, 0), color),
        VertexFormat(glm::vec3(7, -9, 0), color),
        VertexFormat(glm::vec3(4, -12, 0), color),
        VertexFormat(glm::vec3(-4, -12, 0), color),
        VertexFormat(glm::vec3(-7, -9, 0), color),
        VertexFormat(glm::vec3(-7, -1, 0), color),
        VertexFormat(glm::vec3(-6, 0, 0), color),
        VertexFormat(glm::vec3(-7, 1, 0), color),
        VertexFormat(glm::vec3(-7, 9, 0), color),
        VertexFormat(glm::vec3(-2, 8, 0), color),
        VertexFormat(glm::vec3(2, 8, 0), color),
        VertexFormat(glm::vec3(3, 7, 0), color),
        VertexFormat(glm::vec3(3, 3, 0), color),
        VertexFormat(glm::vec3(2, 2, 0), color),
        VertexFormat(glm::vec3(-2, 2, 0), color),
        VertexFormat(glm::vec3(-3, 3, 0), color),
        VertexFormat(glm::vec3(-3, 7, 0), color),
        VertexFormat(glm::vec3(-2, -2, 0), color),
        VertexFormat(glm::vec3(2, -2, 0), color),
        VertexFormat(glm::vec3(3, -3, 0), color),
        VertexFormat(glm::vec3(3, -7, 0), color),
        VertexFormat(glm::vec3(2, -8, 0), color),
        VertexFormat(glm::vec3(-2, -8, 0), color),
        VertexFormat(glm::vec3(-3, -7, 0), color),
        VertexFormat(glm::vec3(-3, -3, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 15, 14, 0, 15,
    15, 1, 2, 16, 15, 2,
    2, 3, 17, 16, 2, 17,
    17, 18, 4, 3, 17, 4,
    4, 18, 22, 23, 4, 22,
    22, 18, 19, 11, 22, 19,
    19, 20, 12, 11, 19, 12,
    12, 13, 21, 20, 12, 21,
    21, 13, 0, 14, 21, 0,
    4, 5, 24, 23, 4, 24,
    24, 25, 6, 5, 24, 6,
    6, 7, 26, 25, 6, 26,
    26, 27, 8, 7, 26, 8,
    8, 9, 28, 27, 8, 28,
    28, 29, 10, 9, 28, 10,
    10, 11, 22, 29, 10, 22};

    number->InitFromData(vertices, indices);
    return number;
}


Mesh* object2D::CreateNine(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(- 8, -6, 0), color),
        VertexFormat(glm::vec3(-8, -9, 0), color),
        VertexFormat(glm::vec3(-5, -12, 0), color),
        VertexFormat(glm::vec3(4, -12, 0), color),
        VertexFormat(glm::vec3(7, -9, 0), color),
        VertexFormat(glm::vec3(7, 9, 0), color),
        VertexFormat(glm::vec3(5, 12, 0), color),
        VertexFormat(glm::vec3(-6, 12, 0), color),
        VertexFormat(glm::vec3(-8, 9, 0), color),
        VertexFormat(glm::vec3(-8, 0, 0), color),
        VertexFormat(glm::vec3(-6, -3, 0), color),
        VertexFormat(glm::vec3(3, -3, 0), color),
        VertexFormat(glm::vec3(3, -8, 0), color),
        VertexFormat(glm::vec3(-4, -8, 0), color),
        VertexFormat(glm::vec3(-4, -6, 0), color),
        VertexFormat(glm::vec3(3, 1, 0), color),
        VertexFormat(glm::vec3(-4, 1, 0), color),
        VertexFormat(glm::vec3(-4, 8, 0), color),
        VertexFormat(glm::vec3(3, 8, 0), color)
    };

    Mesh* number = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 13, 14, 0, 13,
                13, 1, 2, 1, 13, 2,
                2, 3, 12, 13, 2, 12,
                12, 3, 4, 3, 12, 4,
                4, 5, 18, 12, 4, 18,
                18, 5, 6, 5, 18, 6,
                6, 7, 17, 18, 6, 17,
                17, 7, 8, 7, 17, 8,
                8, 9, 16, 17, 8, 16,
                16, 9, 10, 9, 16, 10,
                10, 11, 15, 16, 10, 15 };

    number->InitFromData(vertices, indices);
    return number;
}

Mesh* object2D::CreateTextDMG(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        //D
        VertexFormat(glm::vec3(-26, -12, 0), color),
        VertexFormat(glm::vec3(-26, 12, 0), color),
        VertexFormat(glm::vec3(-14, 12, 0), color),
        VertexFormat(glm::vec3(-10, 8, 0), color),
        VertexFormat(glm::vec3(-10, -8, 0), color),
        VertexFormat(glm::vec3(-14, -12, 0), color),
        //M
        VertexFormat(glm::vec3(-8, -12, 0), color),
        VertexFormat(glm::vec3(-8, 12, 0), color),
        VertexFormat(glm::vec3(0, 4, 0), color),
        VertexFormat(glm::vec3(8, 12, 0), color),
        VertexFormat(glm::vec3(8, -12, 0), color),
        //G
        VertexFormat(glm::vec3(18, -4, 0), color),
        VertexFormat(glm::vec3(18, 0, 0), color),
        VertexFormat(glm::vec3(26, 0, 0), color),
        VertexFormat(glm::vec3(26, -8, 0), color),
        VertexFormat(glm::vec3(22, -12, 0), color),
        VertexFormat(glm::vec3(14, -12, 0), color),
        VertexFormat(glm::vec3(10, -8, 0), color),
        VertexFormat(glm::vec3(10, 8, 0), color),
        VertexFormat(glm::vec3(14, 12, 0), color),
        VertexFormat(glm::vec3(22, 12, 0), color),
        VertexFormat(glm::vec3(26, 8, 0), color),
        VertexFormat(glm::vec3(26, 6, 0), color)
    };

    Mesh* letter = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 0, 1, 2, 3, 4, 5, 0, 1,
                0, 5,
                6, 7, 8, 9, 10,
                15, 14, 13, 12,
                11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                21, 20, 19, 18, 17, 16};
    letter->SetDrawMode(GL_LINE_LOOP);
    letter->InitFromData(vertices, indices);
    return letter;
}

Mesh* object2D::CreateTextSPEED(
    const std::string& name,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        //S 0
        VertexFormat(glm::vec3(-21, 8, 0), color),
        VertexFormat(glm::vec3(-21, 10, 0), color),
        VertexFormat(glm::vec3(-23, 12, 0), color),
        VertexFormat(glm::vec3(-31, 12, 0), color),
        VertexFormat(glm::vec3(-33, 10, 0), color),
        VertexFormat(glm::vec3(-33, 2, 0), color),
        VertexFormat(glm::vec3(-31, 0, 0), color),
        VertexFormat(glm::vec3(-23, 0, 0), color),
        VertexFormat(glm::vec3(-21, -2, 0), color),
        VertexFormat(glm::vec3(-21, -10, 0), color),
        VertexFormat(glm::vec3(-23, -12, 0), color),
        VertexFormat(glm::vec3(-31, -12, 0), color),
        VertexFormat(glm::vec3(-33, -10, 0), color),
        VertexFormat(glm::vec3(-33, -8, 0), color),
        //P 14
        VertexFormat(glm::vec3(-19, -12, 0), color),
        VertexFormat(glm::vec3(-19, 12, 0), color),
        VertexFormat(glm::vec3(-13, 12, 0), color),
        VertexFormat(glm::vec3(-9, 10, 0), color),
        VertexFormat(glm::vec3(-9, 4, 0), color),
        VertexFormat(glm::vec3(-13, 2, 0), color),
        VertexFormat(glm::vec3(-19, 2, 0), color),
        //E 21
        VertexFormat(glm::vec3(3, -10, 0), color),
        VertexFormat(glm::vec3(3, -12, 0), color),
        VertexFormat(glm::vec3(-7, -12, 0), color),
        VertexFormat(glm::vec3(-7, 0, 0), color),
        VertexFormat(glm::vec3(3, 0, 0), color),
        VertexFormat(glm::vec3(-7, 12, 0), color),
        VertexFormat(glm::vec3(3, 12, 0), color),
        VertexFormat(glm::vec3(3, 10, 0), color),
        //E 29
        VertexFormat(glm::vec3(15, -10, 0), color),
        VertexFormat(glm::vec3(15, -12, 0), color),
        VertexFormat(glm::vec3(5, -12, 0), color),
        VertexFormat(glm::vec3(5, 0, 0), color),
        VertexFormat(glm::vec3(15, 0, 0), color),
        VertexFormat(glm::vec3(5, 12, 0), color),
        VertexFormat(glm::vec3(15, 12, 0), color),
        VertexFormat(glm::vec3(15, 10, 0), color),
        //D 37
        VertexFormat(glm::vec3(17, -12, 0), color),
        VertexFormat(glm::vec3(17, 12, 0), color),
        VertexFormat(glm::vec3(29, 12, 0), color),
        VertexFormat(glm::vec3(33, 8, 0), color),
        VertexFormat(glm::vec3(33, -8, 0), color),
        VertexFormat(glm::vec3(29, -12, 0), color)
    };

    Mesh* letter = new Mesh(name);
    std::vector<unsigned int> indices;
    indices = { 11, 12, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                14, 15, 16, 17, 18, 19, 20, 14,
                22, 21, 22, 23, 24, 25, 24, 26, 27, 28, 27, 26, 23,
                30, 29, 30, 31, 32, 33, 32, 34, 35, 36, 35, 34, 31,
                37, 38, 39, 40, 41, 42 };
    letter->SetDrawMode(GL_LINE_LOOP);
    //letter->SetDrawMode(GL_LINES);
    letter->InitFromData(vertices, indices);
    return letter;
}
