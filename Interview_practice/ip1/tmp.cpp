#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;



namespace tmp{
    //GBK:: ���Ծ������⡪��ÿ�ο����� 1 ���� 2 ������ 100 ��̨���ж����߷�

    //�ݹ� recursion 
    int getMethod(int step){       
        if(step==0){
            return 1;
        }else if(step < 0){
            return 0;
        }else{
            return getMethod(step-1) + getMethod(step-2);
        }
    }

    //��̬�滮dynamic programming
    int getMethod_dp(int step,int mem[]){
        if(step<0){
            return 0;
        }else if(step==0){
            return 1;
        }else if(mem[step]!=0){
            return mem[step];
        }else{
            int value = getMethod_dp(step-1,mem)+getMethod_dp(step-1,mem);
            mem[step] = value;
            return value;
        }
    }
    void run(int argc,char** argv){

    }
}









int main(int argc,char** argv){

    tmp::run(argc,argv);
    return 0;
}