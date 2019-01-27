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

void Line::drawLine(char* frameBuffer) {
    // Bresenham's line algorithm with gradient coloring

    Pixel* pixel;

    // Position section
    int colStart = this->getStartPixel().getCol();
    int rowStart = this->getStartPixel().getRow();
    int colEnd = this->getEndPixel().getCol();
    int rowEnd = this->getEndPixel().getRow();

    // Color section
    unsigned char redStart = this->getStartPixel().getRed();
    unsigned char greenStart = this->getStartPixel().getGreen();
    unsigned char blueStart = this->getStartPixel().getBlue();
    unsigned char redEnd = this->getEndPixel().getRed();
    unsigned char greenEnd = this->getEndPixel().getGreen();
    unsigned char blueEnd = this->getEndPixel().getBlue();

    const bool isSteep = (fabs(colEnd - colStart) > fabs(rowEnd - rowStart));

    // Change orientation
    if (isSteep) {
        std::swap(rowStart, colStart);
        std::swap(rowEnd, colEnd);
    }

    // Change starting point
    if (rowStart > rowEnd) {
        std::swap(rowStart, rowEnd);
        std::swap(colStart, colEnd);
    }

    //Setup Const
    const float deltaCol = fabs(colEnd - colStart);
    const float deltaRow = rowEnd - rowStart;
    const float deltaRed = redEnd - redStart;
    const float deltaGreen = greenEnd - greenStart;
    const float deltaBlue = blueEnd - blueStart;

    const int colStep = (colStart < colEnd) ? 1 : -1;
    const float manhattanDist = fabs(deltaCol + deltaRow);
    const float redStep = deltaRed / manhattanDist;
    const float greenStep = deltaGreen / manhattanDist;
    const float blueStep = deltaBlue / manhattanDist;

    // Setup temp variables
    float error = deltaRow / 2.0f;
    int col = colStart;
    unsigned char red = redStart;
    unsigned char green = greenStart;
    unsigned char blue = blueStart;

    // Iterating the longer axis (x or y who has larger delta)
    for (int row = rowStart; row < rowEnd; row++) {

        // Calculate current color
        red += redStep;
        green += greenStep;
        blue += blueStep;

        // Draw pixel
        if (isSteep) {
            pixel = new Pixel(col, row, floor(red), floor(green), floor(blue));
        } else {
            pixel = new Pixel(row, col, floor(red), floor(green), floor(blue));
        }
        pixel->putPixel(frameBuffer);

        // Calculate error, decide to move aside or not for next step
        error -= deltaCol;
        if (error < 0) {
            col += colStep;
            error += deltaRow;
        }
    }
}