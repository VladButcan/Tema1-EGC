#include <iostream>
#include "components/simple_scene.h"
#include "tema/transform2D.h"

namespace tema
{
    class Enemy
    {
    private:
        std::string color;
        int healt;
        int speed;
        float posX;
        float posY;
        float size;
        float radius;
    public:
        Enemy(std::string color, float x, float y, float size);
        std::string getColor();
        void setHealt(int healt);
        int getHealt();
        void setPosX(float x);
        float getPosX();
        void setPosY(float y);
        float getPosY();
        void setSize(float size);
        float getSize();
        void setRadius(float radius);
        float getRadius();
        void setSpeed(int speed);
        int getSpeed();
    };
}