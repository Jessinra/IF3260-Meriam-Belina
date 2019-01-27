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

    int getX() const;
    int getY() const;
    unsigned int getColor() const;

    void setX(int);
    void setY(int);
    void setPos(int, int);
    void setColor(unsigned int);

    void putPixel(char* frameBuffer);
};

#endif