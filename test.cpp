#include <iostream>
#include "master.hpp"
#include "Color.hpp"

using namespace std;

class Runner : public Master{
public:
    Runner(int h = 600, int w = 600) : Master(h, w) {}
    void start(){
        clearWindow();
        Line lin = Line(Pixel(0,0, Color::WHITE), Pixel(this->xend, this->yend, Color::WHITE));
        // for(const Pixel &x : lin.getRefPixelsVector()){
        //     std::cerr<<x.getX()<<" "<<x.getY()<<" "<<x.getColor()<<endl;
        // }
        drawLine(0, 0, lin);
    }
};

int main(){
    Runner run;
    run.start();
    return 0;
}