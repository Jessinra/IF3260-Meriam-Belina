#include <iostream>
#include "MoveableObject.hpp"

MoveableObject::MoveableObject(float x, float y, const std::string &filename): Object(x, y, filename){
    dx = dy = 0;
    speed = 1;
}

MoveableObject::MoveableObject(float x, float y, float _dx, float _dy, float _speed, const std::string &filename): Object(x, y, filename){
    float sum = sqrt(_dx*_dx + _dy*_dy);
    dx = dy = 0;
    if(sum > 0){
        dx = _dx / sum;
        dy = _dy / sum;
    }
    speed = _speed;
}

MoveableObject::MoveableObject(const Object &obj) : Object(obj){
    dx = dy = 0;
    speed = 1;
}

MoveableObject::MoveableObject(float _dx, float _dy, float _speed, const Object &obj) : Object(obj){
    float sum = sqrt(_dx*_dx + _dy*_dy);
    dx = dy = 0;
    if(sum > 0){
        dx = _dx / sum;
        dy = _dy / sum;
    }
    speed = _speed;
}

void MoveableObject::setVector(float _dx, float _dy){
    float sum = sqrt(_dx*_dx + _dy*_dy);
    if(sum > 0){
        dx = _dx / sum;
        dy = _dy / sum;
    }
}

void MoveableObject::move(){
    offset.setX(offset.getX() + dx * speed);
    offset.setY(offset.getY() + dy * speed);
}

void MoveableObject::selfRotation(float x, float y, float theta){
    float yMin, yMax, xMin, xMax;
    bool alreadyloop = false;

    // cout<<"before"<<endl;
    // for(const Line &x : lines){
    //     cout<<x.getStartPixel().getX()<<" "<<x.getStartPixel().getY()<<" "<<x.getEndPixel().getX()<<" "<<x.getEndPixel().getY()<<endl;
    // }
    // cout<<"chages "<<offset.getX()<<" "<<offset.getY()<<" "<<x<<" "<<y<<" "<<theta<<endl;
    x -= offset.getX();
    y -= offset.getY();

    for (Line& line: lines) {
        line.setStartPixel(line.getStartPixel().rotation(x, y, theta));
        line.setEndPixel(line.getEndPixel().rotation(x, y, theta));
        if(alreadyloop){
            xMin = min(xMin, min(line.getStartPixel().getX(), line.getEndPixel().getX()));
            xMax = max(xMax, max(line.getStartPixel().getX(), line.getEndPixel().getX()));
            yMin = min(yMin, min(line.getStartPixel().getY(), line.getEndPixel().getY()));
            yMax = max(yMax, max(line.getStartPixel().getY(), line.getEndPixel().getY()));
        }
        else{
            xMin = min(line.getStartPixel().getX(), line.getEndPixel().getX());
            xMax = max(line.getStartPixel().getX(), line.getEndPixel().getX());
            yMin = min(line.getStartPixel().getY(), line.getEndPixel().getY());
            yMax = max(line.getStartPixel().getY(), line.getEndPixel().getY());
        }
        alreadyloop = true;
    }
    x += offset.getX();
    y += offset.getY();

    // cout<<"after"<<endl;
    // for(const Line &x : lines){
    //     cout<<x.getStartPixel().getX()<<" "<<x.getStartPixel().getY()<<" "<<x.getEndPixel().getX()<<" "<<x.getEndPixel().getY()<<endl;
    // }

    width = xMax - xMin + 1;
    height = yMax - yMin + 1;
}

float MoveableObject::getDx() const{
    return dx;
}

float MoveableObject::getDy() const{
    return dy;
}

float MoveableObject::getSpeed() const{
    return speed;
}

void MoveableObject::setSpeed(float _speed){
    speed = _speed;
}