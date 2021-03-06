#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include "Line.hpp"
#include "Pixel.hpp"
#include "Object.hpp"

class Object{
// Suatu object tersusun atas garix matrix of pixel
protected:
    Pixel offset;
    vector<Line> lines;
    int width;
    int height;
public:
    Object();
    Object(float, float, std::string);
    bool outOfWindow(int, int) const;
    void setPos(Pixel); // change setPos to void
    vector<Line> getLines() const;
    Pixel getPos() const;
    int getWidth() const;
    int getHeight() const;
    const vector<Line> & getRefLines() const;
    const Pixel & getRefPos() const;
};

#endif