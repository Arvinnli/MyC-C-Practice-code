#include <iostream>
#include <stdio.h>

using namespace std;
template <typename T1,typename T2,typename T3>
class Test{
    public:
        T1 t1;
        T2 t2;
        T3 t3;
    private:
    protected:
};
int main(int argc,char** argv){

    Test<int,char,char*> test;

    test.t1 = 100;
    test.t2 = 'h';
    test.t3 = "hello";

    cout << test.t1 << test.t2 << test.t3 << endl;


    return 0;
}