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
public:
    Object();
    Object(int, int, std::string);
    void setPos(Pixel); // change setPos to void
    vector<Line> getLines() const;
    vector<vector<uint32_t>> getImages() const;
    Pixel getPos() const;
    const vector<Line> & getRefLines() const;
    const vector<vector<uint32_t>> & getRefImages() const;
    const Pixel & getRefPos() const;
};

#endif