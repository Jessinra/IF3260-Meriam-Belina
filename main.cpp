#include <iostream>
#include "master.hpp"
#include "Object.hpp"

using namespace std;

class Runner : public Master{
protected:
    Object pesawat, meriam;
public:
    Runner(int h=700, int w = 1000) : Master(h, w) {
        pesawat = Object(0, 0, "object_plane.txt");
        // meriam = Object(0, 0, "meriam.txt");
    }
    void start() {
        while(true){
            clearWindow();
            pesawat.moveLeft(1);
            drawObject(pesawat);
            // cout<<pesawat.getRefPos().getX()<<" "<<pesawat.getRefPos().getY()<<endl;
            if(pesawat.getRefPos().getX() <= -pesawat.getWidth())
                pesawat.setPos(Pixel(xend, 0));
            usleep(800);
        }
    }
};

int main(){
    Runner run;
    run.start();
    return 0;
}