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
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

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
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

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

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner                                   , color),
        VertexFormat(corner + glm::vec3(length / 2, length, 0), color),
        VertexFormat(corner + glm::vec3(length    , 0     , 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length / 2, 0         , 0), color),
        VertexFormat(corner + glm::vec3(length    , length    , 0), color),
        VertexFormat(corner + glm::vec3(length / 2, length * 2, 0), color),
        VertexFormat(corner + glm::vec3(0         , length    , 0), color)
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };
    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* object2D::CreateStar(
const std::string& name,
glm::vec3 leftBottomCorner,
float length,
glm::vec3 color,
bool fill)
{
    glm::vec3 corner = leftBottomCorner;

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

    Mesh* weapon = new Mesh(name);
    std::vector<unsigned int> indices;
    if (!fill) {
        weapon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices = { 0, 1, 2, 0, 2, 3, 4, 5, 3, 5, 6, 7, 5, 6, 7};
    }

    weapon->InitFromData(vertices, indices);
    return weapon;
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

    Mesh* square = new Mesh(name);
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
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
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

    Mesh* square = new Mesh(name);
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
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
}

