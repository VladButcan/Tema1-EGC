

namespace tema
{
    class Enemy
    {
        private:
            int id;
            std::string color;
            int healt;
        
        public:
            Enemy();
            int getId();
            std::string getColor();
            int getHealt();
            void setHealt();
    }
}