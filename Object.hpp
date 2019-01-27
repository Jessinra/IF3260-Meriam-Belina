#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include "Line.hpp"
#include "Pixel.hpp"

class Object{
// Suatu object tersusun atas garix matrix of pixel
protected:
    Pixel offset;
    vector<Line> lines;
    vector<vector<Pixel>> img;
public:
    Object();
    Object(Pixel, std::string);
    Pixel setPos(Pixel);
    vector<Line> getLines();
    vector<vector<Pixel>> getImages();
    Pixel getPos();
    const vector<Line> & getRefLines();
    const vector<vector<Pixel>> & getRefImages();
    const Pixel & getRefPos();
};

#endif