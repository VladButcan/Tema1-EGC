#include <iostream>

namespace tema
{
    class Enemy
    {
    private:
        int id;
        std::string color;
        int healt;
        float posX;
        float posY;

    public:
        Enemy(int id, std::string color, float x, float y);
        int getId();
        std::string getColor();
        int getHealt();
        void setHealt(int healt);
        void setPosX(float x);
        void setPosY(float y);
        float getPosX();
        float getPosY();
        //void setId(int id);
        //void setColor(std::string color);
    };
}