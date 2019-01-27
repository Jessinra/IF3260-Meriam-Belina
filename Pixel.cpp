#include "Pixel.hpp"
#include "Color.hpp"

Pixel::Pixel() {
    x = y = 0;
    col = Color::BLACK;
}

Pixel::Pixel(int _x, int _y) {
    x = _x;
    y = _y;
    col = Color::WHITE;
}

Pixel::Pixel(int _x, int _y, unsigned int color) {
    x = _x;
    y = _y;
    col = color;
}

int Pixel::getX() {
    return this->x;
}

int Pixel::getY() {
    return this->y;
}

unsigned int Pixel::getColor() {
    return this->col;
}

void Pixel::setX(int _x){
    x = _x;
}

void Pixel::setY(int _y){
    y = _y;
}

void Pixel::setPos(int _x, int _y){
    x = _x;
    y = _y;
}

void Pixel::setColor(unsigned int color) {
    this->col = color;
}
