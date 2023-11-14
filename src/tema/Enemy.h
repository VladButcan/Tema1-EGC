#include <iostream>
#include "components/simple_scene.h"
#include "tema/transform2D.h"

namespace tema
{
    class Enemy
    {
    private:
        int id;
        std::string color;
        float healt;
        float posX;
        float posY;
        float size;
        float radius;
        float speed;
    public:
        Enemy(int id, std::string color, float x, float y, float size);
        int getId();
        std::string getColor();
        void setHealt(int healt);
        float getHealt();
        void setPosX(float x);
        float getPosX();
        void setPosY(float y);
        float getPosY();
        void setSize(float size);
        float getSize();
        void setRadius(float radius);
        float getRadius();
        void setSpeed(float speed);
        float getSpeed();
    };
}