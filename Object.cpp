#include "Object.hpp"
#include "Color.hpp"

Object::Object(){
    // initialize offset
    offset.setX(0);
    offset.setY(0);
    offset.setColor(Color::WHITE);

    // initialize lines
    lines.setStartPixel(offset);
    lines.setEndPixel(offset);

    // initialize img
}

Object::Object(int _x, int _y, std::string filename){
    // initialize offset
    offset.setX(x);
    offset.setY(y);
    offset.setColor(Color::WHITE);

    // initialize lines

    // initialize img
    
}

void Object::setPos(Pixel __offset){
    offset.setX(__offset.getX());
    offset.setY(__offset.getY());
}

vector<Line> Object::getLines(){
    return lines;
}

vector<vector<int>> Object::getImages(){
    return img;
}

const vector<Line> & Object::getRefLines(){
    return *lines;
}

const vector<vector<int>> & Object::getRefImages(){
    return *img;
}