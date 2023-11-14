#pragma once
#include <iostream>
#include <chrono>

namespace tema
{
    class Weapon
    {
    private:
        int id;
        std::string color;
        float posX;
        float posY;
        float size;
        float radius;

    public:
        std::chrono::milliseconds elapsedTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;
        bool renderBullet;

    public:
        Weapon(int id, std::string color, float x, float y, float size, float radius);
        int getId();
        std::string getColor();
        void setPosX(float x);
        void setPosY(float y);
        float getPosX();
        float getPosY();
        void setSize(float size);
        float getSize();
        void setRadius(float radius);
        float getRadius();
    };
}