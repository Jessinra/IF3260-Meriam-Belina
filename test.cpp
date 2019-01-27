#include "master.hpp"
#include "Color.hpp"

using namespace std;

class Runner : public Master{
public:
    Runner(int h = 600, int w = 1000) : Master(h, w) {}
    void start(){
        clearWindow();
        Line lin = Line(Pixel(0,0, Color::WHITE), Pixel(this->width-1, this->height-1, Color::WHITE));
        drawLine(0, 0, lin);
    }
};

int main(){
    Runner run;
    run.start();
    return 0;
}