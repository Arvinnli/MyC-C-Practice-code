#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "svpng.inc"
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

#define _S 512

unsigned char img[_S*_S*3];
float px = 0.0f,py=0.0f;

void setpixel(int x,int y);
void lineto(float tx,float ty);
void hilbert(float x, float y, float xi, float xj, float yi, float yj, int n) ;


int main(int argc,char** argv){

    hilbert(0.0f,0.0f,0.0f,_S,_S,0.0f,4);
    svpng(fopen("hilbret.png","wb"),_S,_S,img,0);


    return 0;
}

void hilbert(float x, float y, float xi, float xj, float yi, float yj, int n) {
    if (n) {
        hilbert(x,                   y,                    yi / 2,  yj / 2,  xi / 2,  xj / 2, n - 1);
        hilbert(x + xi / 2,          y + xj / 2,           xi / 2,  xj / 2,  yi / 2,  yj / 2, n - 1);
        hilbert(x + xi / 2 + yi / 2, y + xj / 2 + yj / 2,  xi / 2,  xj / 2,  yi / 2,  yj / 2, n - 1);
        hilbert(x + xi / 2 + yi,     y + xj / 2 + yj,     -yi / 2, -yj / 2, -xi / 2, -xj / 2, n - 1);
    }
    else
        lineto(x + (xi + yi) / 2, y + (xj + yj) / 2);
}

void setpixel(int x, int y) {
    unsigned char* p = img + (y * _S + x) * 3;
    p[0] = p[1] = p[2] = 255;
}

void lineto(float tx, float ty) {
    if (px == tx) {
        int y0 = (int)fminf(py, ty), y1 = (int)fmaxf(py, ty), y;
        for (y = y0; y <= y1; y++)
            setpixel((int)(px), y);
    }
    else if (py == ty) {
        int x0 = (int)fminf(px, tx), x1 = (int)fmaxf(px, tx), x;
        for (x = x0; x <= x1; x++)
            setpixel(x, (int)(py));
    }
    px = tx;
    py = ty;
}
#ifdef __cplusplus
}
#endif