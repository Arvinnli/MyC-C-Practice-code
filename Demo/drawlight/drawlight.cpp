#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include "svpng.inc"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    float sd;
    float emissive;
}Result;



#define W 512
#define H 512

unsigned char img[W*H*3]={0};

float sample(float x,float y);
float trace(float ox,float oy,float dx,float dy);

int main(int argc,char** argv){

    unsigned char* p = img;
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++){
            img[(y*W+x)*3]= (int)fminf(sample((float)x/W,(float)y/H)*255.0f,255.0f);
            img[(y*W+x)*3+1] = img[(y*W+x)*3];
            img[(y*W+x)*3+2] = img[(y*W+x)*3];
        }
    }
    svpng(fopen("basic.png","wb"),W,H,img,0);

    return 0;
}
#define TWO_PI  6.28318530718f
#define N       64
// #define N 360

float sample(float x,float y){
    float sum = 0.0f;
    for(int i=0;i<N;i++){
        // float a = TWO_PI*rand()/RAND_MAX;
        // float a = TWO_PI*i/N;
        float a = TWO_PI * (i + (float)rand() / RAND_MAX) / N;
        sum += trace(x,y,cosf(a),sinf(a));
    }
    return sum/N;
}

float circleSDF(float x, float y, float cx, float cy, float r) {
    float ux = x - cx, uy = y - cy;
    return sqrtf(ux * ux + uy * uy) - r;
}


#define MAX_STEP 10
#define MAX_DISTANCE 2.0f
#define EPSILON 1e-6f

Result unionOp(Result a,Result b){
    return a.sd < b.sd ? a : b;
}
Result intersectOp(Result a,Result b){
    Result r = a.sd > b.sd ? b : a;
    r.sd = a.sd > b.sd ? a.sd : b.sd;
    return r;
}
Result subtractOp(Result a,Result b){
    Result r = a;
    r.sd = (a.sd > -b.sd) ? a.sd : -b.sd;
    return r;
}

Result scene(float x,float y){

    Result a = { circleSDF(x, y, 0.4f, 0.5f, 0.20f), 1.0f };
    Result b = { circleSDF(x, y, 0.6f, 0.5f, 0.20f), 0.0f };
    return unionOp(a, b);
    // return intersectOp(a, b);
    // return subtractOp(a, b);
    // return subtractOp(b, a);

    // Result r1 = {circleSDF(x,y,0.3f,0.3f,0.10f),2.0f};
    // Result r2 = {circleSDF(x,y,0.3f,0.7f,0.05f),0.8f};
    // Result r3 = {circleSDF(x,y,0.7f,0.5f,0.10f),0.0f};
    // return unionOp(unionOp(r1,r2),r3);
    // return result;
}


float trace(float ox,float oy,float dx,float dy){
    float t = 0.0f;
    for(int i=0;i<MAX_STEP&&t<MAX_DISTANCE;i++){
        // float sd = circleSDF(ox+dx*t,oy+dy*t,0.5f,0.5f,0.1f);
        Result result = scene(ox+dx*t,oy+dy*t);
        if(result.sd<EPSILON){
            return result.emissive;
        }
        t += result.sd;
    }
    return 0.0f;
}

#ifdef __cplusplus
}
#endif