#include "Object.hpp"
#include "Color.hpp"
#include <iostream>
#include <fstream>

Object::Object(){
    // initialize offset
    offset.setX(0);
    offset.setY(0);
    offset.setColor(Color::WHITE);

    // initialize lines
    lines[0].setStartPixel(offset);
    lines[0].setEndPixel(offset);
}

Object::Object(int _x, int _y, std::string filename){
    // initialize offset
    offset.setX(_x);
    offset.setY(_y);
    offset.setColor(Color::WHITE);

    // initialize lines
    ifstream inFile;
    inFile.open(filename);

    if (!inFile) {
        cout << "\nError opening file.\n";
        exit(1);
    }
    
    int nline;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    unsigned int colorStart;
    unsigned int colorEnd;

    inFile >> nline;
    for (int i = 0; i < nline; ++i) {
        inFile >> xStart;
        inFile >> yStart;
        inFile >> colorStart;
        inFile >> xEnd;
        inFile >> yEnd;
        inFile >> colorEnd;
        Pixel startpx = Pixel(xStart, yStart, colorStart);
        Pixel endpx = Pixel(xEnd, yEnd, colorEnd);
        Line line = Line(startpx, endpx);
        lines.push_back(line);
    }
    inFile.close();
}

void Object::setPos(Pixel __offset){
    offset = __offset;
}

void Object::moveLeft(int speed){
    offset.setX(offset.getX() - speed);
}

void Object::moveRight(int speed){
    offset.setX(offset.getX() + speed);
}

void Object::moveUp(int speed){
    offset.setY(offset.getY() - speed);
}

void Object::moveDown(int speed){
    offset.setY(offset.getY() + speed);
}

vector<Line> Object::getLines() const{
    return lines;
}

Pixel Object::getPos() const{
    return offset;
}

const vector<Line> & Object::getRefLines() const{
    return lines;
}

const Pixel & Object::getRefPos() const{
    return offset;
}