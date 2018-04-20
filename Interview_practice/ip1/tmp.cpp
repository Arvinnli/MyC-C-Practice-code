#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;



namespace tmp{
    //GBK:: 面试经典问题——每次可以走 1 级或 2 级，上 100 级台阶有多少走法

    typedef  unsigned char dat_t;
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

            Digital operator+(Digital digital){
                dat_t tmp,count = 0;
                Digital dt = *this;
                int m = digital.getLen() > this->getLen() ? digital.getLen() : this->getLen();
                
                for(int i=0;i < m ;i++){
                    tmp = 0xff - this->getDat()[i];
                    if(tmp<digital.getDat()[i] + count){
                        dt.getDat()[i] = digital.getDat()[i] + count - tmp;
                        if(dt.getLen()==m){
                            dt.setLen(dt.getLen()+1);
                        }
                        if(i = m-1){
                            ++m;
                        }
                        count = 1;   
                    }else{
                        dt.getDat()[i] = this->getDat()[i] + count + digital.getDat()[i];
                    }
                }
                return dt;
                for(int i=0;i<digital.getLen()||i<this->getLen();i++){
                    tmp = 0xff - this->_dat[i];
                    if(tmp<(digital.getDat())[i] + count){
                        tmp = (digital.getDat())[i] + count - tmp;
                        count = 1;
                        dt.setLen(dt.getLen()+1);
                        // dt._dat[i] = digital.getDat()[i] - tmp;         
                        dt.getDat()[i] = digital.getDat()[i] - tmp;         
                    }else{
                        dt.getDat()[i] = this->getDat()[i] + count + digital.getDat()[i];
                    }
                    
                }
                return dt;
            }
            // operator=(Digital digital){
            //     *this = digital
            // }
            void showDec(){
                char buf[1024];
                for(int i=_len-1;i>=0;i--){

                }
            }
            void showHex(){
                cout << "0x" ;
                // cout << hex;
                // cout << "len" << _len << endl;
                for(int i=_len-1;i>=0;i--){
                    // cout << "dat[" << i << "]=" << (int)_dat[i] << endl;
                    if(_dat[i]==0){
                        cout << "00";
                    }else if(_dat[i]&0xf0==0){
                        cout << "0";
                        cout << (int)_dat[i];
                    }else{
                        cout << hex << (int)_dat[i] ;     
                    }
                }
                cout << endl;
                cout << dec ;
            }
        private:
            dat_t _dat[1024];
            int _len;
        protected:
    };  


    class BigData{
        public:
            BigData(int dat){
                str = 
            }
            
        private:
            string str;
            int len;
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
    Digital getMethod_dp2(int step, Digital mem[]) {
        int i;
        mem[0] = 1;
        mem[1] = 1; //为什么要提前初始化这一项？
        for (i = 2; i <= step; i++) {
            mem[i] = mem[i-1] + mem[i-2];
            mem[i].showHex();
        }
        return mem[step];
    }
    void run(int argc,char** argv){

        Digital buf[128];
        int n = atoi(argv[1]);
        getMethod_dp2(n,buf);
    }



}









int main(int argc,char** argv){

    tmp::run(argc,argv);
    return 0;
}