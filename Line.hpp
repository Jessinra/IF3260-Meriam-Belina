#include <vector>
#include <math.h>

#include "Pixel.hpp"
using namespace std;

class Line{

    private:

        Pixel startPixel;
        Pixel endPixel;

        vector<Pixel> pixelsVector;

    public:

        Line(Pixel, Pixel);

        void setStartPixel(Pixel);
        void setEndPixel(Pixel);
        Pixel getStartPixel();
        Pixel getEndPixel();
        vector<Pixel> getPixelsVector();

        // Chose one to use, either store line-building-pixel or just draw it to screen every iteration
        void fillPixelsVector();
        void drawLine(char* frameBuffer);


    // TODO:
    // apply color to fill pixel 
};