#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;



namespace tmp{
    //GBK:: 面试经典问题——每次可以走 1 级或 2 级，上 100 级台阶有多少走法

    //递归 recursion 
    int getMethod(int step){       
        if(step==0){
            return 1;
        }else if(step < 0){
            return 0;
        }else{
            return getMethod(step-1) + getMethod(step-2);
        }
    }

    //动态规划dynamic programming
    int getMethod_dp(int step,long long mem[]){
        if(step<0){
            return 0;
        }else if(step==0){
            return 1;
        }else if(mem[step]!=0){
            return mem[step];
        }else{
            long long value = getMethod_dp(step-1,mem)+getMethod_dp(step-1,mem);
            mem[step] = value;
            return value;
        }
    }

    public static int sum2(int step, int mem[]) {
        int i;
        mem[0] = 1;
        mem[1] = 1; //为什么要提前初始化这一项？
        for (i = 2; i <= step; i++) {
            mem[i] = mem[i-1] + mem[i-2];
        }
        return mem[step];
    }

    void run(int argc,char** argv){
        long long buf[10*1024] = {0};
        int n = atoi(argv[1]);
        getMethod_dp(n,buf);

        
        // for(int i=0;buf[i]&&i<10*1024;i++){
        for(int i=0;i<100;i++){
            cout << "buf[" << i << "]=" << buf[i] << endl;
        }


    }
}









int main(int argc,char** argv){

    tmp::run(argc,argv);
    return 0;
}