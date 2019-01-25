#include <vector>
#include "Pixel.hpp"
using namespace std;

class Line{

    private:

        Pixel startPixel;
        Pixel endPixel;

        vector<Pixel> pixelsVector;

    public:

        Line(Pixel, Pixel);

        setStartPixel(Pixel);
        setEndPixel(Pixel);
        Pixel getStartPixel();
        Pixel getEndPixel();
        vector<Pixel> getPixelsVector();
        fillPixelsVector();

    // TODO:
    // apply color to fill pixel 
};