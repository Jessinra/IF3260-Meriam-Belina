#ifndef MASTER_HPP
#define MASTER_HPP

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include "Pixel.hpp"

class Master{
protected:
/* unchangeable */
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int fbfd;
    int screensize;
    char *fbp;
    int xmultiplier;
    int ymultiplier;
    int xadder;
    int yadder;
    int height;
    int width;
/* changeable */
    int xstart;
    int xend;
    int ystart;
    int yend;
    int framejump;
    int offsetcycle;
public:
    Master();
    void assignColor(int, int, unsigned int);
    void assignColor(int, int, int, int);
    void clearWindow();
    void clearWindow(unsigned int);
    void moveWindowUp();
    void draw(int, int, int**, int, int);
    void drawPixels(int, int, Pixel*, int);
};

#endif