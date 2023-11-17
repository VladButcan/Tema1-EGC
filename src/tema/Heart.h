#pragma once
#include <iostream>

namespace tema
{
    class Heart
    {
    public:
        std::string color;
        float posX;
        float posY;
        float size;

    public:
        Heart(std::string color, float posX, float posY, float size);
        std::string getColor();
        void setPosX(float x);
        float getPosX();
        void setPosY(float y);
        float getPosY();
        void setSize(float size);
        float getSize();
    };
}