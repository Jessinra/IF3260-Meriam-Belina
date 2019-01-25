#include "Line.hpp"

Line::Line(Pixel startPixel, Pixel endPixel) {
    setStartPixel(startPixel);
    setEndPixel(endPixel);
    fillPixelsVector();
}

Line::setStartPixel(Pixel startPixel) {
    this->startPixel = startPixel;
}

Line::setEndPixel(Pixel endPixel) {
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

Line::fillPixelsVector() {
    // Bresenham's line algorithm

    vector<Pixel> pixelsVector = this->getPixelsVector();
    Pixel pixel;

    int colStart = this->getStartPixel().getCol();
    int rowStart = this->getStartPixel().getRow();
    int colEnd = this->getEndPixel().getCol();
    int rowEnd = this->getEndPixel().getRow();

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

    const float deltaCol = fabs(colEnd - colStart);
    const float deltaRow = rowEnd - rowStart;
    float error = deltaRow / 2.0f;

    const int colStep = (colStart < colEnd) ? 1 : -1;
    
    int col = colStart;

    for (int row = rowStart; row < rowEnd; row++) {
        if (isSteep) {
            pixel = new Pixel(col, row)
        } else {
            pixel = new Pixel(row, col)
        }
        pixelsVector.push_back(pixel)

        // Calculate error, decide to move aside or not
        error -= deltaCol;
        if (error < 0) {
            col += colStep;
            error += deltaRow;
        }
    }
}
