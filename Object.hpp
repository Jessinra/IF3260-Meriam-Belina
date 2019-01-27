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
    vector<vector<int>> img;
public:
    Object();
    Object(int, int, std::string);
    Pixel setPos(Pixel);
    vector<Line> getLines();
    vector<vector<int>> getImages();
    Pixel getPos();
    const vector<Line> & getRefLines();
    const vector<vector<int>> & getRefImages();
    const Pixel & getRefPos();
};

#endif