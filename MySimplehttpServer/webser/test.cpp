#include <iostream>
#include "ContentType.h"
#include "ArvinnFunc.h"
using namespace std;

int main(int argc,char** argv){
    
    if(argc < 2){
        goto __END_LABEL;
    }
    cout << " what's up?" << endl;
    char buf[128];
    ArvinnFunc::bzero(buf,128);
    cout << ContentType::getpostfix(argv[1],buf) << endl;
    
    cout << "buf: " << buf << endl;

    ArvinnFunc::bzero(buf,128);
    cout << "type : " << ContentType::gettype(argv[1],buf) << endl;


__END_LABEL:
    return 0;
}