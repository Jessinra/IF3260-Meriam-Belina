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
    int xstart;
    int ystart;
    int xend;
    int yend;
    unsigned int color;

    inFile >> nline;
    for (int i = 0; i < nline; ++i) {
        inFile >> xstart;
        inFile >> ystart;
        inFile >> xend;
        inFile >> yend;
        inFile >> color;
        Pixel startpx = Pixel(xstart, ystart, color);
        Pixel endpx = Pixel(xend, yend, color);
        Line line = Line(startpx, endpx);
        lines.push_back(line);
    }
    inFile.close();
}

void Object::setPos(Pixel __offset){
    offset.setX(__offset.getX());
    offset.setY(__offset.getY());
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