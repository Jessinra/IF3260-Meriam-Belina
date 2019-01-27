#include "Object.hpp"
#include "Color.hpp"
#include <iostream>
#include <fstream>

Object::Object(){
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
    int xstart;
    int ystart;
    int xend;
    int yend;
    unsigned int colstart, colend;

    inFile >> nline;
    for (int i = 0; i < nline; ++i) {
        inFile >> xstart;
        inFile >> ystart;
        inFile >> colend;
        inFile >> xend;
        inFile >> yend;
        inFile >> colend;
        Pixel startpx = Pixel(xstart, ystart, colstart);
        Pixel endpx = Pixel(xend, yend, colend);
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