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
// ��C���Ի�������ͼ��

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


�ڼ����ͼ��ѧ�У�Ҫ�ϳɣ�synthesize��һ��ͼ��image��ʱ��ͨ�������ַ�����

1.�滭ÿ����״�������״���ǵ����ء�
2.����ͼ����ÿ�����أ�������sample�������ظ�����ʲô��״��

��һ�־��ǹ�դ����rasterization���㷨���ڶ��ְ�������׷�٣�ray tracing�������߲�����ray marching�����㷨��

�ڶ��������������Ϊ���һ����ѧ�����������ά�ĵ�ɫͼ��Ϳ��Զ���Ϊһ������ 
���磬Բ�̣�disk������ѧ�Ͽɶ���Ϊһ�������� (x - c_x)^2 + (y - c_y)^2 \le r^2����ô��һ�����ڻ������� (10, 10)���뾶 8 ��Բ��ֻ��Ҫ���� f(x, y) Ϊ��

int f(int x, int y) {
    return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;
}

// y/3 ���� �� 3����������Σ�
#endif