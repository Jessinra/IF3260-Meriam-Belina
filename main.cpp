#include <iostream>
#include <utility>
#include <ctime>
#include "master.hpp"
#include "Object.hpp"
#include "MoveableObject.hpp"

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
        pesawat.setPos(Pixel(xend, 0));
        meriam.setPos(Pixel((xend - meriam.getWidth())/2, yend - meriam.getHeight() - 2));
        peluru.setPos(Pixel((xend - peluru.getWidth())/2, yend - meriam.getHeight() - peluru.getHeight() - 2));
        vector<pair<MoveableObject, bool> > planes;
        vector<MoveableObject> bullets;
        // MoveableObject cannon(meriam);
        planes.push_back({MoveableObject(-1, 0, 1, pesawat), false});
        bullets.push_back(MoveableObject(0, -1, 2, peluru));
        for(int i=1;;i=(i+1)%1200){
            // for(const MoveableObject & obj : planes)
            //     cout<<"plane "<<obj.getRefPos().getX()<<" "<<obj.getRefPos().getY()<<endl;
            // for(const MoveableObject & obj : bullets)
            //     cout<<"peluru "<<obj.getRefPos().getX()<<" "<<obj.getRefPos().getY()<<endl;

            // draw
            clearWindow();

            for(const pair<MoveableObject, bool> & obj : planes)
                drawObject(obj.first);
            for(const MoveableObject & obj : bullets)
                drawObject(obj);
            drawObject(meriam);

            // move shit
            vector<pair<MoveableObject, bool> >tmpp;
            vector<MoveableObject>tmpb;
            for(pair<MoveableObject, bool> & obj : planes){
                obj.first.move();
                if(obj.first.outOfWindow(yend, xend)){
                    if(!obj.second){
                        obj.first.setPos(pesawat.getRefPos());
                        tmpp.push_back(obj);
                    }
                }
                else{
                    tmpp.push_back(obj);
                }
                
            }
            for(MoveableObject & obj : bullets){
                obj.move();
                if(obj.outOfWindow(yend, xend)){
                    obj.setPos(peluru.getRefPos());
                }
            }
            
            // very slow shit
            for(const MoveableObject & objb : bullets){
                bool bisa = true;
                for(pair<MoveableObject, bool> & objp : tmpp){
                    if(overlap(objp.first, objb)){
                        objp.first.setVector(-1, 2);
                        objp.second = true;
                        bisa = false;
                    }
                }
                if(bisa){
                    tmpb.push_back(objb);
                }
            }
            planes = tmpp;
            bullets = tmpb;

            if(i % 400 == 0)
                bullets.push_back(MoveableObject(0, -1, 2, peluru));
            if(i % 800 == 0)
                planes.push_back({MoveableObject(-1, 0, 1, pesawat), false});

            usleep(6000);
        }
    }
    bool overlap(const Object &p, const Object &q){
        int a,b,c,d,e,f,g,h;
        a = p.getRefPos().getX();
        b = p.getRefPos().getY();
        c = a + p.getWidth() - 1;
        d = b + p.getHeight() - 1;
        e = q.getRefPos().getX();
        f = q.getRefPos().getY();
        g = e + q.getWidth() - 1;
        h = f + q.getHeight() - 1;
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