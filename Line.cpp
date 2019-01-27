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

Pixel Line::getStartPixel() {
    return this->startPixel;
}

Pixel Line::getEndPixel() {
    return this->endPixel;
}

vector<Pixel> Line::getPixelsVector() {
    return this->pixelsVector;
}

void Line::fillPixelsVector() {
    // Bresenham's line algorithm with gradient coloring

    vector<Pixel> pixelsVector = this->getPixelsVector();
    Pixel* pixel;

    // Position section
    int xStart = this->getStartPixel().getX();
    int yStart = this->getStartPixel().getY();
    int xEnd = this->getEndPixel().getX();
    int yEnd = this->getEndPixel().getY();

    // Color section
    unsigned int colorStart = this->getStartPixel().getColor();
    unsigned int colorEnd = this->getEndPixel().getColor();

    const bool isSteep = (abs(xEnd - xStart) > abs(yEnd - yStart));

    // Change orientation
    if (isSteep) {
        std::swap(xStart, yStart);
        std::swap(xEnd, yEnd);
    }

    // Change starting point
    if (yStart > yEnd) {
        std::swap(yStart, yEnd);
        std::swap(xStart, xEnd);
    }

    //Setup Const
    const float deltaX = fabs(xEnd - xStart);
    const float deltaY = yEnd - yStart;
    const float deltaRed = ((colorEnd & 0xff0000) - (colorStart & 0xff0000)) >> 16;
    const float deltaGreen = ((colorEnd & 0xff00) - (colorStart & 0xff00)) >> 8;
    const float deltaBlue = ((colorEnd & 0xff) - (colorStart & 0xff));

    const int colStep = (xStart < xEnd) ? 1 : -1;
    const float manhattanDist = fabs(deltaX + deltaY);
    const float redStep = deltaRed / manhattanDist;
    const float greenStep = deltaGreen / manhattanDist;
    const float blueStep = deltaBlue / manhattanDist;

    // Setup temp variables
    float error = deltaY / 2.0f;
    int col = xStart;
    unsigned char red = colorStart & 0xff0000;
    unsigned char green = colorStart & 0xff00;
    unsigned char blue = colorStart & 0xff;

    // Iterating the longer axis (x or y who has larger delta)
    for (int row = yStart; row < yEnd; row++) {

        // Calculate current color
        red += redStep;
        green += greenStep;
        blue += blueStep;

        // Add pixel to vector
        unsigned int color = (int)floor(red) << 16 + (int)floor(green) << 8 + (int)floor(blue);
        if (isSteep) {
            pixel = new Pixel(col, row, color);
        } else {
            pixel = new Pixel(row, col, color);
        }
        pixelsVector.push_back(*pixel);

        // Calculate error, decide to move aside or not for next step
        error -= deltaX;
        if (error < 0) {
            col += colStep;
            error += deltaY;
        }
    }
}
