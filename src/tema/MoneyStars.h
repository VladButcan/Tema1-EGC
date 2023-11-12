#pragma once
#include <iostream>

namespace tema
{
    class MoneyStars
    {
    private:
        std::string color;
        float posX;
        float posY;
        float size;

    public:
        MoneyStars(std::string color, float x, float y, float size);
        std::string getColor();
        void setPosX(float x);
        void setPosY(float y);
        float getPosX();
        float getPosY();
        void setSize(float size);
        float getSize();
    };
}