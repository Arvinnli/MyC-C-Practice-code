#include <stdio.h>
#include <math.h>
const int w = 24 ;
const int h = 12 ;

int triangle(int x, int y){
    // return (x-10)*(x-10) + (y-10)*(y-10) < 64;
    return (abs(x)<=y);
}
int func(int x,int y){
    return (triangle((x+(y/3)*3+3)%6-2,y%3))&&(triangle(x-11,y));
}

int main(int argc,char** argv){
    
    int x,y;
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            printf(func(x,y)?"* ":"  ");
        }
        puts("");
    }


    return 0;
}

#ifdef __TEMP_SPACE
// 用C语言画以如下图形

                      *
                    * * *
                  * * * * *
                *           *
              * * *       * * *
            * * * * *   * * * * *
          *           *           *
        * * *       * * *       * * *
      * * * * *   * * * * *   * * * * *
    *           *           *           *
  * * *       * * *       * * *       * * *
* * * * *   * * * * *   * * * * *   * * * * *


在计算机图形学中，要合成（synthesize）一个图像（image）时，通常有两种方法：

1.绘画每个形状，填充形状覆盖的像素。
2.对于图像中每个像素，采样（sample）该像素覆盖了什么形状。

第一种就是光栅化（rasterization）算法，第二种包括光线追踪（ray tracing）、光线步进（ray marching）等算法。

第二种做法可以理解为设计一个数学函数，例如二维的单色图像就可以定义为一个函数 
例如，圆盘（disk）在数学上可定义为一个隐函数 (x - c_x)^2 + (y - c_y)^2 \le r^2，那么画一个置于画布中心 (10, 10)、半径 8 的圆盘只需要定义 f(x, y) 为：

int f(int x, int y) {
    return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;
}

// y/3 行数 × 3（半个三角形）
#endif