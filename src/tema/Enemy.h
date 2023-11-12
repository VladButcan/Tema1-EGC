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
        int healt;
        float posX;
        float posY;
        float size;
        float radius;
        glm::mat3 modelMatrix;

    public:
        Enemy(int id, std::string color, float x, float y, float size, glm::mat3 modelMatrix);
        int getId();
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
        glm::mat3 getMatrix();
        void translateMatrix(float x, float y);
        void scaleMatrix(float x, float y);
        //void setId(int id);
        //void setColor(std::string color);
    };
}