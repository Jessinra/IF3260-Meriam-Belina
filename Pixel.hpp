#include <vector>
using namespace std;

class Pixel {
   private:
    int col;
    int row;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

   public:
    Pixel();
    Pixel(int, int);
    Pixel(int row, int col, unsigned char red, unsigned char green, unsigned char blue);

    int getRow();
    int getCol();
    unsigned char getRed();
    unsigned char getGreen();
    unsigned char getBlue();

    void setRow(int);
    void setCol(int);
    void setColor(unsigned char red, unsigned char green, unsigned char blue);

    void putPixel(char* frameBuffer);
};