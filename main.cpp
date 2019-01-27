#include <iostream>
#include "master.hpp"
#include "Object.hpp"

using namespace std;

class Runner : public Master{
protected:
    Object pesawat, meriam, peluru;
public:
    Runner(int h=700, int w = 1000) : Master(h, w) {
        pesawat = Object(0, 0, "object_plane.txt");
        meriam = Object(0, 0, "object_gun.txt");
        peluru = Object(0, 0, "object_bullet.txt");
    }
    void start() {
        cout<<meriam.getHeight()<<" "<<meriam.getWidth()<<endl;
        cout<<peluru.getHeight()<<" "<<peluru.getWidth()<<endl;
        meriam.setPos(Pixel((xend - meriam.getWidth())/2, yend - meriam.getHeight() - 2));
        peluru.setPos(Pixel((xend - peluru.getWidth())/2, yend - meriam.getHeight() - peluru.getHeight() - 2));
        pesawat.setVector(-1, 0);
        pesawat.setSpeed(1);
        peluru.setVector(0, -1);
        peluru.setSpeed(1);
        while(true){
            // clear Window
            clearWindow();

            // move pesawat
            drawObject(pesawat);
            drawObject(meriam);
            drawObject(peluru);
            pesawat.move();
            peluru.move();

            // cout<<pesawat.getRefPos().getX()<<" "<<pesawat.getRefPos().getY()<<endl;
            if(pesawat.outOfWindow(yend, xend))
                pesawat.setPos(Pixel(xend, 0));

            if(peluru.outOfWindow(yend, xend))
                peluru.setPos(Pixel((xend - peluru.getWidth())/2, yend - meriam.getHeight() - peluru.getHeight() - 2));

            

            usleep(800);
        }
    }
};

int main(){
    Runner run;
    run.start();
    return 0;
}