#include <stdio.h>
#include "../stdfx.h"

// file codec : GBK
// gcc 生成at&t汇编文件
// gcc -S test.c  
// gcc -S -masm=att test.c
// gcc -S -masm=intel test.c 生成intel风格汇编
int main(int argc,char* argv[]){
//0x407f60 0x407fa0
    volatile void* ptr = NULL;
    // volatile void* ptr1 = printf;
    ptr = 0x407fa0;
    int (*func)(const char*,...);
    func = ptr;
    // printf("ptr:0x%x\n",ptr);
    // printf("ptr1:0x%x\n",ptr1);
    func("Line%d:hello arvinn\n",__LINE__);


    return 0;
}