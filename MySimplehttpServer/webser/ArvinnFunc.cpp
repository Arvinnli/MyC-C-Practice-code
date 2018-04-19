#include "ArvinnFunc.h"


void ArvinnFunc::bzero(char* ptr,int n){
    int i;
    for(i=0;i<n;i++){
        ptr[i] = 0;
    }
}