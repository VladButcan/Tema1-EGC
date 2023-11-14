#include <iostream>
#include "components/simple_scene.h"
#include "tema/transform2D.h"

namespace tema
{
    class Bullet
    {
    private:
        int id;
        std::string color;
        float posX;
        float posY;
        float size;
        float angle;
        float radius;
    public:
        float damage;
        float speed;

    public:
        Bullet(int id, std::string color, float x, float y, float size, float angle);
        int getId();
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