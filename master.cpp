#include <iostream>
#include "master.hpp"
#include "Pixel.hpp"

Master::Master(int h, int w){
    xstart = ystart = 0;
    yend = h;
    xend = w;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (!fbfd) {
        printf("Error: cannot open framebuffer device.\n");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("Error reading fixed information.\n");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading variable information.\n");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory	
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fbfd, 0);
    if ((long int)fbp == -1) {
        printf("Error: failed to map framebuffer device to memory.\n");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    xmultiplier = (vinfo.bits_per_pixel/8);
    xadder = (vinfo.xoffset) * xmultiplier;
    ymultiplier = finfo.line_length;
    yadder = vinfo.yoffset * finfo.line_length;
}

void Master::assignColor(int x, int y, unsigned int color){
    int location = x * xmultiplier + xadder + y * ymultiplier + yadder;
    *((unsigned int *) (fbp + location)) = color;
}

void Master::assignColor(int x1, int y1, int x2, int y2){
    int location1 = x1 * xmultiplier + xadder + y1 * ymultiplier + yadder;
    int location2 = x2 * xmultiplier + xadder + y2 * ymultiplier + yadder;
    *((unsigned int *) (fbp + location1)) = *((unsigned int *) fbp + location2);
}

void Master::clearWindow(){
    memset(fbp, 0, (yend*ymultiplier + yadder));
}

void Master::clearWindow(unsigned int color){
    for (int  y = ystart; y < yend; y++ ){
        for (int x = xstart; x < xend; x++ ) {
            assignColor(x, y, color);
        }
    }
}

void Master::moveWindowUp(){
    for (int  y = ystart; y < yend-framejump; y += framejump){
        int location1 = xadder + y*ymultiplier + yadder;
        int location2 = location1 + framejump * ymultiplier;
        memcpy(fbp+location1, fbp+location2, framejump*(1+vinfo.yoffset) * finfo.line_length);
	}
    memset(fbp + (yend-framejump)*ymultiplier + yadder, 0, framejump*(ymultiplier + yadder));
}

void Master::draw(int offsetx, int offsety, int **img, int height, int width) {
    for(int y = max(0, offsety); y < height; y++) {
        if(y + offsety >= this->yend) break;
        for(int x = max(0, offsetx); x < width; x++) {
            if(x + offsetx >= this->xend) break;
            assignColor(x + offsetx, y + offsety, img[y][x]);
        }
    }
}

void Master::draw(int offsetx, int offsety, const vector<vector<int> > &img){
    for(int y = max(0, -offsety); y < (int)img.size(); y++) {
        if(y + offsety >= this->yend) break;
        for(int x = max(0, -offsetx); x < img[y].size(); x++) {
            if(x + offsetx >= this->xend) break;
            assignColor(x + offsetx, y + offsety, img[y][x]);
        }
    }
}

void Master::drawPixel(int offsetx, int offsety, const Pixel &pix){
    int x = offsetx + pix.getX();
    int y = offsety + pix.getY();
    if(x >=0 && x < this->xend && y >=0 && y < this->yend)
        assignColor(x, y, pix.getColor());
}

void Master::drawLine(int offsetx, int offsety, const Line &line){
    // Bresenham's line algorithm with gradient coloring

    // Position section
    int xStart = line.getStartPixel().getX();
    int yStart = line.getStartPixel().getY();
    int xEnd = line.getEndPixel().getX();
    int yEnd = line.getEndPixel().getY();

    // Color section
    int colorStart = line.getStartPixel().getColor();
    int colorEnd = line.getEndPixel().getColor();

    //Setup Const
    const float deltaX = xEnd - xStart;
    const float deltaY = yEnd - yStart;
    const float deltaRed = ((colorEnd & 0xff0000) - (colorStart & 0xff0000)) >> 16;
    const float deltaGreen = ((colorEnd & 0xff00) - (colorStart & 0xff00)) >> 8;
    const float deltaBlue = ((colorEnd & 0xff) - (colorStart & 0xff));
    const float manhattanDist = fabs(deltaX) + fabs(deltaY)+1;
    const float redStep = deltaRed / manhattanDist;
    const float greenStep = deltaGreen / manhattanDist;
    const float blueStep = deltaBlue / manhattanDist;
    const int xStep = deltaX>=0?1 : -1;
    const int yStep = deltaY>=0?1 : -1;

    float red = (colorStart & 0xff0000)>>16;
    float green = (colorStart & 0xff00)>>8;
    float blue = colorStart & 0xff;

    if(xStart == xEnd){
        if(xStart+offsetx >=this->xstart && xStart+offsetx < this->xend){
            for(int y = yStart;y != yEnd + yStep;y += yStep){
                unsigned int color = ((unsigned int)floor(red) << 16) + ((unsigned int)floor(green) << 8) + ((unsigned int)floor(blue));

                if(offsety+y>=this->ystart && offsety+y<this->yend){
                    assignColor(offsetx+xStart, offsety+y, color);
                }

                red += redStep;
                green += greenStep;
                blue += blueStep;
            }
        }
        return;
    }

    int y = yStart;
    const float deltaErr = fabs(deltaY/deltaX);
    float error = 0;
    for(int x=xStart;x!=xEnd + xStep;){
        unsigned int color = ((unsigned int)floor(red) << 16) + ((unsigned int)floor(green) << 8) + ((unsigned int)floor(blue));
        
        if(offsetx+x >= this->xstart && offsetx+x < this->xend &&
            offsety+y >= this->ystart && offsety+y < this->yend){
            assignColor(offsetx+x, offsety+y, color);
        }

        if(error >= 0.5){
            y += yStep;
            error -= 1;
        }
        else{
            error += deltaErr;
            x += xStep;
            if(error >= 0.5){
                y += yStep;
                error -= 1;
            }
        }

        if(y < 0) break;

        red += redStep;
        green += greenStep;
        blue += blueStep;
    }
}

void Master::drawObject(const Object& obj){
    int offx = obj.getRefPos().getX();
    int offy = obj.getRefPos().getY();
    for(const Line &ln : obj.getRefLines()){
        drawLine(offx, offy, ln);
    }
}

void Master::drawPixels(int offsetx, int offsety, Pixel* pixels, int numberPixels) {
    for(int i = 0; i < numberPixels; i++) {
        // assignColor
        // assignColor(offsetx + Pixel[i].getRow())
    }
}
