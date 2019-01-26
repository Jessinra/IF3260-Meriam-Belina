#include "Pixel.hpp"

Pixel::Pixel() {
    setRow(-999);
    setCol(-999);
    setColor(0, 0, 0);  //Default color black (blend with background)
}

Pixel::Pixel(int row, int col) {
    setRow(row);
    setCol(col);
    setColor(255, 255, 255);  //Default color white
}

Pixel::Pixel(int row, int col, unsigned char red, unsigned char green, unsigned char blue) {
    setRow(row);
    setCol(col);
    setColor(red, green, blue);
}

int Pixel::getRow() {
    return this->row;
}

int Pixel::getCol() {
    return this->col;
}

unsigned char Pixel::getRed() {
    return this->red;
}

unsigned char Pixel::getGreen() {
    return this->green;
}

unsigned char Pixel::getBlue() {
    return this->blue;
}

void Pixel::setCol(int col) {
    this->col = col;
}

void Pixel::setRow(int row) {
    this->row = row;
}

void Pixel::setColor(unsigned char red, unsigned char green, unsigned char blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}
