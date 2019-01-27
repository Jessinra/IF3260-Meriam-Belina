#ifndef LINE_HPP
#define LINE_HPP

#include <vector>
#include <cmath>
#include <cstdlib>

#include "Pixel.hpp"
using namespace std;

class Line{

    protected:

        Pixel startPixel;
        Pixel endPixel;

        vector<Pixel> pixelsVector;

    public:

        Line(Pixel, Pixel);

        void setStartPixel(Pixel);
        void setEndPixel(Pixel);
        Pixel getStartPixel() const;
        Pixel getEndPixel() const;
        vector<Pixel> getPixelsVector() const;
        const vector<Pixel> & getRefPixelsVector() const;

        // Chose one to use, either store line-building-pixel or just draw it to screen every iteration
        void fillPixelsVector();
};

#endif