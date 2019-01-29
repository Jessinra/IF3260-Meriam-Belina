#include <cmath>
#include "Pixel.hpp"
#include "Color.hpp"

Pixel::Pixel() {
    x = y = 0;
    col = Color::BLACK;
}

Pixel::Pixel(float _x, float _y) {
    x = _x;
    y = _y;
    col = Color::WHITE;
}

Pixel::Pixel(float _x, float _y, unsigned int color) {
    x = _x;
    y = _y;
    col = color;
}

float Pixel::getX() const{
    return this->x;
}

float Pixel::getY() const{
    return this->y;
}

unsigned int Pixel::getColor() const{
    return this->col;
}

void Pixel::setX(float _x){
    x = _x;
}

void Pixel::setY(float _y){
    y = _y;
}

void Pixel::setPos(float _x, float _y){
    x = _x;
    y = _y;
}

void Pixel::setColor(unsigned int color) {
    this->col = color;
}

void Pixel::rotation(float pointX, float pointY, float theta) {
    x -= pointX;
    y -= pointY;

    float sinTheta = sin(theta);
    float cosTheta = cos(theta);

    float xnew = x*cosTheta - y*sinTheta;
    float ynew = x*sinTheta + y*cosTheta;

    x = xnew + pointX;
    y = ynew + pointY;
}