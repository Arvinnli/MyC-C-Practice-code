

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
unsigned int array1_size = 16;                                          // �ų� ASCII ���ǰ 16 ���ַ�
unsigned char array1[160]      = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };    // һ���ֵ�
unsigned char array2[256 * 512];                                               // 256 ��Ӧ ASCII ���
const char *secret       = __MAGICWORDS;                              // ���Զ�ȡ������
int iThreshold           = CACHE_HIT_THRESHOLD;                            // ��ȡʱ�䷧ֵ

unsigned char temp = 0;

void victim_function(int x){
    if(x < array1_size){
        temp &= array2[array1[x] * 512];
    }
}

void readMemoryByte(int malicious_x,uint8 value[2],int score[2]){
    
}