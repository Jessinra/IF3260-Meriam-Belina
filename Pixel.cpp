#include "Pixel.hpp"

Pixel::Pixel(int row, int col) {
    setRow(row);
    setCol(col);
    setColor(0xFFFFFF);
}

Pixel::Pixel(int row, int col, int color) {
    setRow(row);
    setCol(col);
    setColor(color);
}

int Pixel::getRow() {
    return this->row;
}

int Pixel::getCol() {
    return this->col;
}

int Pixel::getColor() {
    return this->color;
}

void Pixel::setCol(int col) {
    this->col = col;
}

void Pixel::setRow(int row) {
    this->row = row;
}

void Pixel::setColor(int color) {
    this->color = color;
}
