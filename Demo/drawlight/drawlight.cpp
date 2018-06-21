#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include "svpng.inc"
#include <time.h>
#ifdef __cplusplus
extern "C"{
#endif

typedef struct{
    float sd;
    float emissive;         //光强度
    float reflectivity;     //反射
    float eta;              //折射率
}Result;

#define TWO_PI 6.28318530718f
#define W 512
#define H 512
#define N 64
#define MAX_STEP 64
#define MAX_DISTANCE 5.0f
#define EPSILON 1e-6f
#define BIAS 1e-4f
#define MAX_DEPTH 3

unsigned char img[W*H*3]={0};

float sample(float x,float y);
// float trace(float ox,float oy,float dx,float dy);
float trace(float ox,float oy,float dx,float dy,int depth);
float planeSDF(float x,float y,float px,float py,float nx,float ny);
Result scene(float x,float y);
void gradient(float x,float y,float* nx,float* ny);
int refract(float ix,float iy,float nx,float ny,float eta,float* rx,float* ry);


int main(int argc,char** argv){
    char buf[40] = {0};
    // srand((unsigned)time(NULL));
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



float circleSDF(float x, float y, float cx, float cy, float r) {
    float ux = x - cx, uy = y - cy;
    return sqrtf(ux * ux + uy * uy) - r;
}


float boxSDF(float x, float y, float cx, float cy, float theta, float sx, float sy) {
    float costheta = cosf(theta), sintheta = sinf(theta);
    float dx = fabs((x - cx) * costheta + (y - cy) * sintheta) - sx;
    float dy = fabs((y - cy) * costheta - (x - cx) * sintheta) - sy;
    float ax = fmaxf(dx, 0.0f), ay = fmaxf(dy, 0.0f);
    return fminf(fmaxf(dx, dy), 0.0f) + sqrtf(ax * ax + ay * ay);
}

float planeSDF(float x, float y, float px, float py, float nx, float ny) {
    return (x - px) * nx + (y - py) * ny;
}

Result unionOp(Result a, Result b) {
    return a.sd < b.sd ? a : b;
}

Result intersectOp(Result a, Result b) {
    return a.sd > b.sd ? a : b;
}

Result subtractOp(Result a, Result b) {
    Result r = a;
    r.sd = (a.sd > -b.sd) ? a.sd : -b.sd;
    return r;
}


void gradient(float x, float y, float* nx, float* ny) {
    *nx = (scene(x + EPSILON, y).sd - scene(x - EPSILON, y).sd) * (0.5f / EPSILON);
    *ny = (scene(x, y + EPSILON).sd - scene(x, y - EPSILON).sd) * (0.5f / EPSILON);
}

void reflect(float ix, float iy, float nx, float ny, float* rx, float* ry) {
    float idotn2 = (ix * nx + iy * ny) * 2.0f;
    *rx = ix - idotn2 * nx;
    *ry = iy - idotn2 * ny;
}

int refract(float ix, float iy, float nx, float ny, float eta, float* rx, float* ry) {
    float idotn = ix * nx + iy * ny;
    float k = 1.0f - eta * eta * (1.0f - idotn * idotn);
    if (k < 0.0f)
        return 0; // 全内反射
    float a = eta * idotn + sqrtf(k);
    *rx = eta * ix - a * nx;
    *ry = eta * iy - a * ny;
    return 1;
}

float trace(float ox, float oy, float dx, float dy, int depth) {
    float t = 1e-3f;
    float sign = scene(ox, oy).sd > 0.0f ? 1.0f : -1.0f; // 内还是外？
    for (int i = 0; i < MAX_STEP && t < MAX_DISTANCE; i++) {
        float x = ox + dx * t, y = oy + dy * t;
        Result r = scene(x, y);
        if (r.sd * sign < EPSILON) { // 判断是否到达表面时要考虑内外
            float sum = r.emissive;
            if (depth < MAX_DEPTH && (r.reflectivity > 0.0f || r.eta > 0.0f)) {
                float nx, ny, rx, ry, refl = r.reflectivity;
                gradient(x, y, &nx, &ny);
                nx *= sign; ny *= sign; // 在内的话，要反转法线
                if (r.eta > 0.0f) {
                    if (refract(dx, dy, nx, ny, sign < 0.0f ? r.eta : 1.0f / r.eta, &rx, &ry))
                        sum += (1.0f - refl) * trace(x - nx * BIAS, y - ny * BIAS, rx, ry, depth + 1);
                    else
                        refl = 1.0f; // 全内反射
                }
                if (refl > 0.0f) {
                    reflect(dx, dy, nx, ny, &rx, &ry);
                    sum += refl * trace(x + nx * BIAS, y + ny * BIAS, rx, ry, depth + 1);
                }
            }
            return sum;
        }
        t += r.sd * sign;
    }
    return 0.0f;
}

float sample(float x, float y) {
    float sum = 0.0f;
    for (int i = 0; i < N; i++) {
        float a = TWO_PI * (i + (float)rand() / RAND_MAX) / N;
        sum += trace(x, y, cosf(a), sinf(a), 0);
    }
    return sum / N;
}


Result scene(float x,float y){
  
    Result a = { circleSDF(x, y, -0.1f, -0.1f, 0.1f), 5.0f, 0.0f, 0.0f };
    Result b = {    boxSDF(x, y, 0.5f, 0.5f, 0.0f, 0.3, 0.2f), 0.0f, 0.2f, 1.5f};
    return unionOp(a, b);


#if 0
    Result a = {circleSDF(x,y,0.4f,0.2f,0.1f),3.0f};
    Result b = {boxSDF(x,y,0.3f,0.8f,TWO_PI/16.0f,0.1f,0.1f),0.0f};
    Result c = {boxSDF(x,y,0.8f,0.3f,TWO_PI/16.0f,0.1f,0.1f),0.0f};
    return unionOp(unionOp(a,b),c);
    // Result a = {circleSDF(x,y,0.5f,0.5f,0.2f),1.0f};
    // Result b = {planeSDF(x,y,0.0f,0.5f,0.0f,1.0f),0.8f};
    // // return intersectOp(a,b);
    // Result c = {capsuleSDF(x,y,0.4f,0.4f,0.6f,0.6f,0.1f),1.8f};
    // Result d = {boxSDF(x,y,0.5f,0.5f,TWO_PI/16.0f,0.2f,0.1)-0.051f,0.9f};
    // Result f = { triangleSDF(x, y, 0.5f, 0.2f, 0.8f, 0.8f, 0.3f, 0.6f)-0.02f, 1.0f };
    // return f;

    // Result a = { circleSDF(x, y, 0.4f, 0.5f, 0.20f), 1.0f };
    // Result b = { circleSDF(x, y, 0.6f, 0.5f, 0.20f), 0.8f };
    // return unionOp(a, b);
    // return intersectOp(a, b);
    // return subtractOp(a, b);
    // return subtractOp(b, a);

    // Result r1 = {circleSDF(x,y,0.3f,0.3f,0.10f),2.0f};
    // Result r2 = {circleSDF(x,y,0.3f,0.7f,0.05f),0.8f};
    // Result r3 = {circleSDF(x,y,0.7f,0.5f,0.10f),0.1f};
    // return unionOp(unionOp(r1,r2),r3);
    // return result;
#endif
}





#ifdef __cplusplus
}
#endif