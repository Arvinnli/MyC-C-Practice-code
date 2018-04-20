#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;



namespace tmp{
    //GBK:: 面试经典问题——每次可以走 1 级或 2 级，上 100 级台阶有多少走法

    typedef dat_t unsigned char;
    #define max 0xff;

    class Digital{
        public:
            Digital(){
                _len = 0;
            }
            Digital(dat_t dat){
                _len = 1;
                _dat[0] = dat;
            }
            int getLen(){
                return _len;
            }
            void setLen(int len){
                _len = len;
            }
            virtual void setDat(Digital digital){
                for(int i=0;i<digital.getLen();i++){
                    _dat[i] = digital.getDat()[i];
                }
                setLen(digital.getLen());
            }
            dat_t* getDat(){
                return _dat;
            }

            operator +(Digital digital){
                dat_t tmp,count = 0;
                for(int i=0;i<digital.getLen()||i<this->getLen();i++){
                    tmp = 0xffffffff - this->_dat[i];
                    if(tmp<(digital.getDat())[i] + count){
                        tmp = (digital.getDat())[i] + count - tmp;
                        count = 1;
                    }else{
                        this->getDat()[i] = this->getDat()[i] + count + digital.getDat())[i];
                    }
                    this->_len++;
                }
            }
            void show(){
                 for(int i=0;i<_len;i++){
                    cout << "dat[" << i << "]=" << dat[i] << endl;
                }
            }
        private:
            dat_t _dat[1024];
            int _len;
        protected:
    };  


    class A{
        public:
            A(){}
            int* getDat(){
                return dat;
            }
            void show(){
                for(int i=0;i<10;i++){
                    cout << "dat[" << i << "]=" << dat[i] << endl;
                }
            }
        private:
            int dat[10];
        protected:
    };


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

    int getMethod_dp1(int step, long long mem[]) {
        int i;
        mem[0] = 1;
        mem[1] = 1; //为什么要提前初始化这一项？
        for (i = 2; i <= step; i++) {
            mem[i] = mem[i-1] + mem[i-2];
        }
        return mem[step];
    }

    void run(int argc,char** argv){
        // long long buf[101] = {0};
        // int n = atoi(argv[1]);
        // getMethod_dp1(n,buf);

        
        // // for(int i=0;buf[i]&&i<10*1024;i++){
        // for(int i=0;i<101;i++){
        //     cout << "buf[" << i << "]=" << buf[i] << endl;
        // }
        Digital d

    }

    // // Fibonacci
    // F[n+1] = F[n] + F[n-1];
    // F[n] = F[n-1] + F[n-2];
    // ....
    // F[2] = F[1] + F[0];
    // F[1] = 1;F[0] =0;


}









int main(int argc,char** argv){

    tmp::run(argc,argv);
    return 0;
}