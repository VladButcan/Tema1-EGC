#include <iostream>
#include "components/simple_scene.h"
#include "tema/transform2D.h"

namespace tema
{
    class Bullet
    {
    private:
        std::string color;
        float posX;
        float posY;
        float size;
        float angle;
        float radius;
    public:
        int damage;
        int speed;

    public:
        Bullet(std::string color, float x, float y, float size, float angle);
        std::string getColor();
        void setPosX(float x);
        float getPosX();
        void setPosY(float y);
        float getPosY();
        void setSize(float size);
        float getSize();
        void setAngle(float angle);
        float getAngle();
        void setRadius(float radius);
        float getRadius();
    };
}