#include <cmath>
#include <iostream>
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

Pixel Pixel::rotation(float pointX, float pointY, float theta) {
    int resultX = x;
    int resultY = y;

    resultX -= pointX;
    resultY -= pointY;

    float sinTheta = sin(theta*PI/180);
    float cosTheta = cos(theta*PI/180);

    float xnew = resultX*cosTheta - resultY*sinTheta;
    float ynew = resultX*sinTheta + resultY*cosTheta;

    resultX = xnew + pointX;
    resultY = ynew + pointY;

    return Pixel(resultX, resultY);
}