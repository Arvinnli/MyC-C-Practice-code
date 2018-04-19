

#define __DEBUG
#define __TRYTIMES      50

#define __MAGICWORDS    \
"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"     
#define __MAGICWORDSCOUNT (sizeof(__MAGICWORDS)-1)

#define CACHE_HIT_THRESHOLD (50)


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <intrin.h>
#pragma optimize("gt",on)

typedef unsigned char uint8;
unsigned int array1_size = 16;                                          // 排除 ASCII 码表前 16 个字符
unsigned char array1[160]      = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };    // 一个字典
unsigned char array2[256 * 512];                                               // 256 对应 ASCII 码表
const char *secret       = __MAGICWORDS;                              // 测试读取的数据
int iThreshold           = CACHE_HIT_THRESHOLD;                            // 读取时间阀值

unsigned char temp = 0;

void victim_function(int x){
    if(x < array1_size){
        temp &= array2[array1[x] * 512];
    }
}

void readMemoryByte(int malicious_x,uint8 value[2],int score[2]){
    
}