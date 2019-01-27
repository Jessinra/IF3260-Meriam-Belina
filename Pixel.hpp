#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
using namespace std;

class Pixel {
   private:
    int x;
    int y;
    unsigned int col;

   public:
    Pixel();
    Pixel(int, int);
    Pixel(int, int, unsigned int);

    int getX();
    int getY();
    unsigned int getColor();

    void setX(int);
    void setY(int);
    void setPos(int, int);
    void setColor(unsigned int);
};

#endif