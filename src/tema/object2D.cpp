#include "object2D.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0     , 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0     , length, 0), color)
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
        VertexFormat(corner + glm::vec3(length / 2         , 0         , 0), color),
        VertexFormat(corner + glm::vec3(length / 2 + length, 0         , 0), color),
        VertexFormat(corner + glm::vec3(2 * length         , length    , 0), color),
        VertexFormat(corner + glm::vec3(length / 2 + length, length * 2, 0), color),
        VertexFormat(corner + glm::vec3(length / 2         , length * 2, 0), color),
        VertexFormat(corner + glm::vec3(0                  , length    , 0), color)
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
        VertexFormat(corner + glm::vec3(0                  , length             , 0), color),
        VertexFormat(corner + glm::vec3(length / 2         , length * 2         , 0), color),
        VertexFormat(corner + glm::vec3(length             , length             , 0), color),
        VertexFormat(corner + glm::vec3(length / 2         , 0                  , 0), color),
        VertexFormat(corner + glm::vec3(length / 2         , length - length / 5, 0), color),
        VertexFormat(corner + glm::vec3(length / 2 + length, length - length / 5, 0), color),
        VertexFormat(corner + glm::vec3(length / 2 + length, length + length / 5, 0), color),
        VertexFormat(corner + glm::vec3(length / 2         , length + length / 5, 0), color)
    };

    Mesh* weapon = new Mesh(name);
    std::vector<unsigned int> indices;
    if (!fill) {
        weapon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices = { 0, 1, 2, 3, 0, 2, 4, 5, 6, 7, 4, 6};
    }

    weapon->InitFromData(vertices, indices);
    return weapon;
}
//Mesh* object2D::CreateTransparentSquare(
//    const std::string& name,
//    glm::vec3 leftBottomCorner,
//    float length,
//    glm::vec4 color)
//{
//    glm::vec3 corner = leftBottomCorner;
//
//    std::vector<VertexFormat> vertices =
//    {
//        VertexFormat(corner, color),
//        VertexFormat(corner + glm::vec3(length, 0, 0), color),
//        VertexFormat(corner + glm::vec3(length, length, 0), color),
//        VertexFormat(corner + glm::vec3(0, length, 0), color)
//    };
//
//    Mesh* square = new Mesh(name);
//    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3 };
//
//    square->InitFromData(vertices, indices);
//    return square;
//}

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
        VertexFormat(corner + glm::vec3(length / 8      , 11 * length / 16 , 0), color),
        VertexFormat(corner + glm::vec3(11 * length / 8 , 11 * length / 16 , 0), color),
        VertexFormat(corner + glm::vec3(3 * length / 4  , 5 * length / 16  , 0), color),
        VertexFormat(corner + glm::vec3(length / 2      , length / 2       , 0), color),
        VertexFormat(corner + glm::vec3(19 * length / 16, 0                , 0), color),
        VertexFormat(corner + glm::vec3(3 * length / 4  , 9 * length / 8   , 0), color),
        VertexFormat(corner + glm::vec3(5 * length / 16 , 0                , 0), color),
        VertexFormat(corner + glm::vec3(length          , length / 2       , 0), color)
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

