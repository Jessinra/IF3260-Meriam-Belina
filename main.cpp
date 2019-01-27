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
        pesawat.setPos(Pixel(xend, 0));
        pesawat.setVector(-1, 0);
        pesawat.setSpeed(1);
        meriam.setPos(Pixel((xend - meriam.getWidth())/2, yend - meriam.getHeight() - 2));
        peluru.setPos(Pixel((xend - peluru.getWidth())/2, yend - meriam.getHeight() - peluru.getHeight() - 2));
        peluru.setVector(0, -1);
        peluru.setSpeed(2);
        bool hitted = false;
        while(true){
            // clear Window
            clearWindow();

            // move pesawat
            drawObject(pesawat);
            drawObject(meriam);
            drawObject(peluru);
            pesawat.move();
            peluru.move();

            if(pesawat.outOfWindow(yend, xend)){
                if(hitted){
                    hitted = false;
                    pesawat.setVector(-1, 0);
                }
                pesawat.setPos(Pixel(xend, 0));
            }

            if(peluru.outOfWindow(yend, xend)){
                peluru.setPos(Pixel((xend - peluru.getWidth())/2, yend - meriam.getHeight() - peluru.getHeight() - 2));
            }

            if(overlap(pesawat, peluru)){
                if(!hitted){
                    hitted = true;
                    pesawat.setVector(-1, 2);
                    // pesawat.setPos(Pixel(xend, 0));
                    peluru.setPos(Pixel((xend - peluru.getWidth())/2, yend - meriam.getHeight() - peluru.getHeight() - 2));
                }
            }

            usleep(6000);
        }
    }
    bool overlap(const Object &p, const Object &q){
        int a,b,c,d,e,f,g,h;
        a = p.getRefPos().getX();
        b = p.getRefPos().getY();
        c = a + p.getWidth();
        d = b + p.getHeight();
        e = q.getRefPos().getX();
        f = q.getRefPos().getY();
        g = e + q.getWidth();
        h = f + q.getHeight();
        if(a > g || e > c) return false;
        if(b > h || f > d) return false;
        return true;
    }
};

int main(){
    Runner run;
    run.start();
    return 0;
}