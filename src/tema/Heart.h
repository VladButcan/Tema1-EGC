#pragma once
#include <iostream>

namespace tema
{
    class Heart
    {
    public:
        std::string color;
        std::string rightCircle;
        float centerLeftCircle;
        float centerRightCircle;
        float radius;

    public:
        Heart(std::string color, float centerLeftCircle, float centerRightCircle, float radius);
        /*int getId();
        std::string getColor();
        void setPosX(float x);
        void setPosY(float y);
        float getPosX();
        float getPosY();
        void setSize(float size);
        float getSize();*/
        //void setId(int id);
        //void setColor(std::string color);
    };
}