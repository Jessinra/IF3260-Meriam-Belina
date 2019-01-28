#include "Object.hpp"
#include "Color.hpp"
#include <iostream>
#include <fstream>

Object::Object(){
}

Object::Object(float _x, float _y, std::string filename){
    // initialize offset
    offset = Pixel(_x, _y);

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
    int yMin;
    int yMax;
    int xMin;
    int xMax;
    unsigned int colorStart;
    unsigned int colorEnd;

    inFile >> nline;
    for (int i = 0; i < nline; ++i) {
        inFile >>dec>> xStart;
        inFile >> yStart;
        inFile >>hex>> colorStart;
        inFile >>dec>> xEnd;
        inFile >> yEnd;
        inFile >>hex>> colorEnd;
        if(i == 0){
            xMin = min(xStart, xEnd);
            xMax = max(xStart, xEnd);
            yMin = min(yStart, yEnd);
            yMax = max(yStart, yEnd);
        }
        else{
            xMin = min(yMin, min(xStart, xEnd));
            xMax = max(xMax, max(xStart, xEnd));
            yMin = min(yMin, min(yStart, yEnd));
            yMax = max(yMax, max(yStart, yEnd));
        }
        Pixel startpx = Pixel(xStart, yStart, colorStart);
        Pixel endpx = Pixel(xEnd, yEnd, colorEnd);
        Line line = Line(startpx, endpx);
        lines.push_back(line);
    }
    height = yMax - yMin + 1;
    width = xMax - xMin + 1;
    inFile.close();
}

void Object::setPos(Pixel __offset){
    offset = __offset;
}

bool Object::outOfWindow(int h, int w) const{
    return (offset.getX() >= w || offset.getY() >= h || offset.getX() <= -width || offset.getY()<=-height);
}

int Object::getWidth() const{
    return width;
}

int Object::getHeight() const{
    return height;
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