#include <iostream>
#include "Line.hpp"

Line::Line(Pixel startPixel, Pixel endPixel) {
    setStartPixel(startPixel);
    setEndPixel(endPixel);
    fillPixelsVector();  // Not needed if line displayed as it goes
}

void Line::setStartPixel(Pixel startPixel) {
    this->startPixel = startPixel;
}

void Line::setEndPixel(Pixel endPixel) {
    this->endPixel = endPixel;
}

Pixel Line::getStartPixel() const{
    return this->startPixel;
}

Pixel Line::getEndPixel() const{
    return this->endPixel;
}

vector<Pixel> Line::getPixelsVector() const{
    return this->pixelsVector;
}

const vector<Pixel> & Line::getRefPixelsVector() const{
    return this->pixelsVector;
}

void Line::fillPixelsVector() {
    // Bresenham's line algorithm with gradient coloring
    
    pixelsVector.clear();

    // Position section
    int xStart = this->getStartPixel().getX();
    int yStart = this->getStartPixel().getY();
    int xEnd = this->getEndPixel().getX();
    int yEnd = this->getEndPixel().getY();

    // Color section
    int colorStart = this->getStartPixel().getColor();
    int colorEnd = this->getEndPixel().getColor();

    //Setup Const
    const float deltaX = xEnd - xStart;
    const float deltaY = yEnd - yStart;
    const float deltaRed = ((colorEnd & 0xff0000) - (colorStart & 0xff0000)) >> 16;
    const float deltaGreen = ((colorEnd & 0xff00) - (colorStart & 0xff00)) >> 8;
    const float deltaBlue = ((colorEnd & 0xff) - (colorStart & 0xff));
    const float manhattanDist = fabs(deltaX) + fabs(deltaY)+1;
    const float redStep = deltaRed / manhattanDist;
    const float greenStep = deltaGreen / manhattanDist;
    const float blueStep = deltaBlue / manhattanDist;
    const int xStep = deltaX>=0?1 : -1;
    const int yStep = deltaY>=0?1 : -1;

    float red = (colorStart & 0xff0000)>>16;
    float green = (colorStart & 0xff00)>>8;
    float blue = colorStart & 0xff;

    if(xStart == xEnd){
        for(int y = yStart;y != yEnd + yStep;y += yStep){
            unsigned int color = ((unsigned int)floor(red) << 16) + ((unsigned int)floor(green) << 8) + ((unsigned int)floor(blue));

            pixelsVector.push_back(Pixel(xStart, y, color));

            red += redStep;
            green += greenStep;
            blue += blueStep;
        }
        return;
    }

    int y = yStart;
    const float deltaErr = fabs(deltaY/deltaX);
    float error = 0;
    for(int x=xStart;x!=xEnd + xStep;){
        unsigned int color = ((unsigned int)floor(red) << 16) + ((unsigned int)floor(green) << 8) + ((unsigned int)floor(blue));

        pixelsVector.push_back(Pixel(x, y, color));

        if(error >= 0.5){
            y += yStep;
            error -= 1;
        }
        else{
            error += deltaErr;
            x += xStep;
            if(error >= 0.5){
                y += yStep;
                error -= 1;
            }
        }

        if(y < 0) break;

        red += redStep;
        green += greenStep;
        blue += blueStep;
    }
}